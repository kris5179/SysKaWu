#include "connection.h"
#include <iostream>
#include <string>
#include "sqlite3.h"
#include "szyfrowanie.h"
using namespace std;

Connection::Connection(const string& filename)
      : filename_(filename) {
    int rc = sqlite3_open(filename.c_str(), &dbHandle_);
    if (rc != SQLITE_OK) {
        cerr << "Błąd otwierania bazy danych: " << sqlite3_errmsg(dbHandle_) << endl;
    } else {
        cout << "Pomyślnie otwarto bazę danych" << endl;
    }
}

void Connection::Insert(int id, int privilege, const string& username, const string& password){
    string hash = passHashing(password);
    const char* query = "INSERT INTO users (id, privilege, login, password) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    

    // stmt, prepare, bind są po to, żeby chronić nas przed SQL injection
    // moim zdaniem jest to bardziej czytelne niż konkatenacja stringów
    if (sqlite3_prepare_v2(dbHandle_, query, -1, &stmt, nullptr) == SQLITE_OK){
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_bind_int(stmt, 2, privilege);
        sqlite3_bind_text(stmt, 3, username.c_str(), username.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, hash.c_str(), hash.length(), SQLITE_STATIC);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            queryError();
        } else {
            cout << "Zapytanie wykonano pomyślnie" <<  endl;
        }
    } else {
        prepStmtError();
    }
}

void Connection::SelectById(int id){ 
    const char* query = "SELECT * FROM users WHERE id=?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbHandle_, query, -1, &stmt, nullptr) == SQLITE_OK){
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            queryError();
        } else {
            cout << "Zapytanie wykonano pomyślnie" << endl;
        }
    } else {
        prepStmtError();
    }
}

void Connection::SelectByPrivilege(int privilege){
    const char* query = "SELECT * FROM users WHERE privilege=?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbHandle_, query, -1, &stmt, nullptr) == SQLITE_OK){
        sqlite3_bind_int(stmt, 1, privilege);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            queryError();
        } else {
            cout << "Zapytanie wykonano pomyślnie" << endl;
        }
    } else {
        prepStmtError();
    }
}

void Connection::SelectByLogin(string username){
    const char* query = "SELECT * FROM users WHERE login='?';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbHandle_, query, -1, &stmt, nullptr) == SQLITE_OK){
        sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            queryError();
        } else {
            cout << "Zapytanie wykonano pomyślnie" << endl;
        }
    } else {
        prepStmtError();
    }
}

void Connection::Delete(int id){
    const char* query = "DELETE FROM users WHERE id=?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbHandle_, query, -1, &stmt, nullptr) == SQLITE_OK){
        sqlite3_bind_int(stmt, 1, id); 
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            queryError();
        } else {
            cout << "Zapytanie wykonano pomyślnie" << endl;
        }
    } else {
        prepStmtError();
    }
}

void Connection::Delete(string username){
    const char* query = "DELETE FROM users WHERE login='?';";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(dbHandle_, query, -1, &stmt, nullptr) == SQLITE_OK){
        sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            queryError();
        } else {
            cout << "Zapytanie wykonano pomyślnie" << endl;
        }
    } else {
        prepStmtError();
    }
}

Connection::~Connection(){
    if (dbHandle_ != nullptr) {
        sqlite3_close(dbHandle_);
        cout << "Baza danych bezpiecznie zamknięta" << endl;
    }
}

void Connection::queryError(){
    cerr << "Błąd podczas wykonywania zapytania: " << sqlite3_errmsg(dbHandle_) << endl;
}

void Connection::prepStmtError(){
    cerr << "Błąd podczas przygotowywania zapytania: " << sqlite3_errmsg(dbHandle_) << endl;
}
