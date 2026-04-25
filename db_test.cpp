    // basic komendy do sqlite:
    // sqlite3 <nazwa_bazy>.db -> otwiera sqlite i pracujesz na bazie <nazwa_bazy>
    // wiadomo można robić query typu create table, select, itd.
    // .schema <nazwa_tabeli> - pokazuje, jakie pola mamy w tabeli
    // lub .headers on i wtedy pokazuja sie dane w tabeli razem z naglowkami
    //
#include "db_test.h"
#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std;

int databaseConnection(sqlite3* &db, string filename){
    int connection{};
    // c_str(), bo funkcje sqlite3 przyjmuja char* a nie string
    // Można użyć ":memory:" zamiast filename.c_str, żeby stworzyć tymczasową bazę danych w RAM-ie - może się przydać do testów
    //
    connection = sqlite3_open(filename.c_str(), &db);

    if (connection != SQLITE_OK){
        cerr << "Błąd otwierania bazy danych" << endl;
        return{};
    }

    cout << "Baza otwarta pomyślnie" << endl;
    return connection;
}

void databasePasswordEntry(sqlite3* &db, const char* password){
    string passwordAsString = password;
    char* errorMessage = nullptr;
    string query = "INSERT INTO users (id, privilege, login, password)"
                            "VALUES   (67, 7     , 'ex_login', '" + passwordAsString + "');";

    // jeszcze nie wiem co tu robia nullptr-`y, nie mialem czasu tego kminic
    // jest cos z callbackami i instrukcjami dla wierszy, ktore query znajdzie, ale przy insercie to bez zanczenia
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (rc != SQLITE_OK){
        cerr << "Błąd SQL: " << errorMessage << endl;
        sqlite3_free(errorMessage);
        return;
    }

    cout << "Dane pomyślnie dodane do bazy" << endl;
}
