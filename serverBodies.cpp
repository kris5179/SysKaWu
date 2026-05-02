#include <cstring>
#include <iostream>
#include "serverHeader.h"
using namespace std;

Server::Server(int port) : serverSocket(-1), port(port) { //serverSocket(-1) inicjalizuje nam socket w bezpiecznym stanie (potem go nadpisujemy), nie trzeba się martwić o błędy w inicjalizacji spowodowane śmieciami z poprzednich połaczeń
    memset(&serverAddress, 0, sizeof(serverAddress)); //kulturalna rezerwacja pamięci
}

Server::~Server() {
    if (serverSocket >= 0) {
        close(serverSocket);
    }
}

bool Server::createSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); //mówiąc krótko, to argumenty tutaj to kolejno: int domain, int type, int protocol, domain czy ipv4 cy v6, type to jaki typ gniazda tutaj stream cyli TCP, protocol jest dane 0 czyli domyślny (tu TCP)

    if (serverSocket < 0) { //samograj, jak nie zmieniło się czyl idalej jest stan bezpieczny to wywala błąd
        cout << "Błąd tworzenia socketa" << endl;
        return false;
    }

    return true;
}

bool Server::configureSocket() {
    int opt = 1; //opt od operator, z dokumentacji wynika że SO_REUSEADDR oczekuje włączenia lub wyłączenia przez int 0 lub 1 (0 nie działa, 1 działa)

    //tłumacząc to poniżej, jak wsadzisz funkcje do ifa to się wykonuje, więc tutaj za jednym zamachem wykonujemy funkcje która ustawia konfiguracje socketa, jak nie zadziała, czyli zwróci coś mniejszego od zera to wiemy że coś poszło nie tak i rzuca błędem
    //serverSocket czyli socket jaki wczesniej stowrzyliśmy, SOL_SOCKET ustawia nam opcje "na poziomie" socketa, nie chciałi mi się w to bardziej zagłębiać więc tylko tyle wiem, SO_REUSEADDR powoduje że serwer recyklinguje sobie adresy ip jakie wcześniej użył
    //w momencie w którym wyłączymy serwer i od razu go włączymy, bez tego funcja binding wywali nam błąd że adres jest już w użyciu (te adresy nawet jak program przestaje działać to system je ma odhaczone jako używane przez pewien czas)

    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        cout << "Błąd ustawiania konfiguracji socketa" << endl;
        return false;
    }

    return true;
}

bool Server::bindSocket() {
    //korzystamy tu z wbudowanej struktury headera unixowego te trzy linjiki w dół odpowiadają za wypełnienie trzech pół tej struktury
    serverAddress.sin_family = AF_INET;  //AF_INET to stała która oznacza że adres jest typu IPv4
    serverAddress.sin_addr.s_addr = INADDR_ANY; //to przypisanie ustawia opcję, która binduje socket do wszystkich adresów na urządzeniu, w praktyce to znaczy że nie ważne na jaki interfejs (wifi ethernet) wyślesz zapytanie, serwer je odczyta
    serverAddress.sin_port = htons(port); //ustawianie portu na którym socket nasłuchuje

    //ten sam trik co wczesniej, ale tutaj wykorzystujemy wbudowaną systemową funkcje bind i jako parametry wsadzamy tą konfiguracje jaka nam sę podoba
    //do sockAddress jest pointer, ponieważ bind oczekuje tutaj parametru który jest pointerem do structa
    //bind zwraca 0 jak się uda, -1 jak się nie uda

    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        cout << "Błąd bindowania socketa" << endl;
        return false;
    }

    return true;
}

bool Server::listenSocket() {

    //łapiecie chyba idee z tym if
    //korzystamy tu z wbudowanej funkcji systemowej listen, jako pierwszy argument dajemy to na jakim sockecie system ma nasłuchiwać,
    //to drugie, SOMAXCONN to parametr tego jak długa może być kolejka oczekiwania na obsługę przez pakiety.
    //listen zwraca 0 jak działa, -1 jak nie działa

    if (listen(serverSocket, SOMAXCONN) < 0) {
        cout << "Błąd nasłuchu socketa" << endl;
        return false;
    }
    return true;
}

bool Server::start() {

    //nieco łopatologiczne sprawdzenie czy wszystko działa i jak wszystko dziala to potwierdzenie odpalenia się serwera

    if (!createSocket()) { return false; }

    if (!configureSocket()) { return false; }

    if (!bindSocket()) { return false; }

    if (!listenSocket()) { return false; }

    cout << "Server nasłuchuje na porcie: " << port << endl;
    return true;
}

void Server::run() {

    const char* filename = "test.txt"; //myśle że użycie tu pointera jest wskazane, wskazujemy plik jaki będziemy wysyłać


    while (true) {
        int clientSocket = accept(serverSocket, NULL, NULL);

        //if poniżej, jeśli clientsocket jest mniejszy od 0 znaczy że coś nie działa, nwm utrata połączenia w/e, wtedy rzucamy błędem i wracamy do początku pętli
        if (clientSocket < 0) {
            cout << "Błąd akceptacji socketa" << endl;
            return;
        }

        //TODO: przepisać to tak żeby było mniej wcięć bo Krzysiu wylewu dostanie
        //TODO: fajnie że serwer serwuje rzeczy, ale jeszcze fajniej jakby obsługiwał rzeczy od klientów

        //otwieramy plik o nazwie którą podajemy w zmiennej filename. jeśli program nie może otworzyć pliku, zamyka połączenie z klientem żeby nie tracić czasu na wysyłanie czegoś czego nie ma.
        //continue powoduje że program leci dalej do kolejnej iteracji pętli i czeka na połączenie z klientem. Idea jest taka że jak ci plik nie zadziałał to powtórz cały proces raz jeszcze bo a nuż zadziała za drugim razem

        FILE* input = fopen(filename, "rb"); //rb - read, binary mode
        if (!input) {
            cout << "Nie można otworzyć pliku: " << filename << endl;
            close(clientSocket);
            continue;
        }

        //tworzymy tu bufor, czyli wskazujemy jaką maksymalną wielkośc pliku serwer będzie wysyłał i za razem ile bajtów powinien spodziewać się klient
        //zanim serwer wyśle coś do sieci, pobiera do bufora z dysku plik, a potem z bufora do sieci, tak do końca to chyba chodzi o to by zwolnić proces który używa dysku i to wszystko robić po kolei a nie wszystko na raz

        char buffer[4096];

        //ciągła pętla niżej czyta plik kawałek po kawałku, pętla w tej pętli wysyła ten kawałek przez sieć

        while (true) {

            //fread generalnie zwraca format size_t czyli tyle bajtów ile ostało przeczytane, sieze_t to po prostu "standard unsigned type for sizes and counts of bytes"

            size_t bytesRead = fread(buffer, 1, sizeof(buffer), input); //czytanie kawałka pliku, tutaj wielkość tego kawalka to 1 bajt, parametr sizeof(buffr) to oznaczenie jak dużo kawałków jest do przeczytania

            //jeszcze co do tego sizeof(buffer), znaczy to, że funcja fread będzie starąła się czytać tyle ile może z tego pliku (czyli tyle ile ma bufora),
            //jeśli plik jest mniejszy niż wielkość bufora to tym zajmuje się funcja poniżej

            if (bytesRead == 0) { //jeśli nie przeczyta nic, to znaczy że mamy koniec pliku, czyli przerywamy czytanie
                break;
            }

            size_t totalSent = 0; //totalsent to licznik tego ile kawałków wysłaliśmy przez sieć, czyli naturalnie (he he) zaczynamy od zera

            //totalsent < bytesread jest lepsze niż totalsent <= bytesread, bo totalsent jest inherentnie mniejsze od bytesread (totalsent zaczyna się od zera) i jak prześledzicie jak to się wykonuje to przy ostatniej iteracji, gdzie wysylamy ostatni bajt,
            //total send jest mniejszy od bytes read, bo bytes read inkrementujemy na końcu, więc jak damy <= to spowodujemy że na końcu będziemy chcieli aby program wysłał pustą wiadomość, co założe się ze będzie pain in the ass

            while (totalSent < bytesRead) {

                //ssize_t to wersja signed size_t
                //argumenty send, to kolejno sockfd, czyli deskryptor jaki dostajemy z accept() (wszystko w linuxie jest plikiem to się z tym wiąże). potem buffer + totalsent to pointer do miejsca gdzie zaczynają się dane które chcemy wysłać
                //potem bytesRead - totalSent to ilość bajtów które chcemy dalej wysłać z tego bufora, 0 na końcu to flagi, nie mam pojęcia czym one są chyba nie potrzebne, ustaiwone na 0 czyli normalne zachowanie

                ssize_t sent = send(clientSocket,buffer + totalSent,bytesRead - totalSent,0);

                //send() zwraca 0 dla sukcesu, coś mniejszego od 0 dla błędu

                if (sent < 0) {
                    cout << "Wysłanie nie udane" << endl;
                    totalSent = bytesRead; // jeśli totalsent wynosi tyle samo ile kawałków wyciągneliśmy z pliku, to przerywa całą pętle, bo oznacza to że wyslaliśmy w sieć cały plik
                    break;
                }

                //dobra ten static_cast tuaj jest od tego (bo pan w artykule kazał), bo sent ma znak (-/+) a totalsent nie ma znaku, więc aby zadbać o bezpieczeństwo, konwertujemy sent do size_t
                //a to że sent ma znak, wynika tego że send z powodu którego nie pamiętam ale jest w dokumentacji, po prostu zwraca rzeczy w ssize_t

                totalSent += static_cast<size_t>(sent);
            }
        }

    }

}





