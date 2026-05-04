//
// Created by wikipetan on 1.05.2026.
//

#ifndef SERWER_SOCKETHEADER_H
#define SERWER_SOCKETHEADER_H
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

class Server {
    public:
        //argument konstruktora to numer portu, ułatwi to na szybko zmiane portu na którym słuchać i odpowiadac będzie program
        Server(int port);
        ~Server();
        bool start(); //dzięki typowi bool możemy łatwo wychwycić błąd przy inicjalizacji serwera
        void run(); //główna funkcja ogarniająca akceptowanie i handlingowanie połączeń
    private: //póki co private jako good practice ale można to potem zmienić
        int serverSocket;
        int port;

        sockaddr_in serverAddress; //z netinet/in.h deklarujemy strukturę która przechowuje adrs i port do którego będzie bindowany serwer

        //wszystko jako bool, zdecydowanie łatwiej zrobić error handling
        bool createSocket();
        bool configureSocket(); //funkcja jest po to, aby nie dostawać błędu "addres already in use" po każdym restarcie serwera
        bool bindSocket();
        bool listenSocket();
};



#endif //SERWER_SOCKETHEADER_H
