#include "connection.h"
#include <iostream>
#include <sodium.h>
#include <sodium/crypto_pwhash.h>
#include <string>
#include "sqlite3.h"
#include "passwords.h"
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


void Connection::Insert(int privilege, const string& username, const string& password){
    string hash = passHashing(password);
    const char* query = "INSERT INTO Uzytkownicy (Privilege, Login, Password) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;

    // stmt, prepare, bind są po to, żeby chronić nas przed SQL injection
    // moim zdaniem jest to bardziej czytelne niż konkatenacja stringów
    if (sqlite3_prepare_v2(dbHandle_, query, -1, &stmt, nullptr) == SQLITE_OK){
        sqlite3_bind_int(stmt, 1, privilege);
        sqlite3_bind_text(stmt, 2, username.c_str(), username.length(), SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, hash.c_str(), hash.length(), SQLITE_STATIC);

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
    const char* query = "SELECT * FROM Uzytkownicy WHERE ID=?;";
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
    const char* query = "SELECT * FROM Uzytkownicy WHERE Privilege=?;";
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

void Connection::Delete(int id){
    const char* query = "DELETE FROM Uzytkownicy WHERE ID=?;";
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
    const char* query = "DELETE FROM Uzytkownicy WHERE Login=?;";
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

queryResponse Connection::Login(string login, string password) {
    queryResponse response;
    const char* query = "SELECT * FROM Uzytkownicy WHERE Login=?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(dbHandle_, query, -1, &stmt, nullptr) == SQLITE_OK){
        sqlite3_bind_text(stmt, 1, login.c_str(), login.length(), SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            cout << "Zapytanie wykonano pomyślnie" << endl;

            // sprawdzenie czy haslo sie zgadza za pomoca libsodium
            const char* storedHash = (const char*)sqlite3_column_text(stmt, 3);
            if (crypto_pwhash_str_verify(
                storedHash,
                password.c_str(),
                password.size()) != 0) 
            {
                cout << "Hasło się nie zgadza" << endl;
                response.id = -1;
                response.privilege = -1;
                response.login = "";
                response.found = false;
                return response;
            }

            else {
                response.found = true;
                // 0 - 1 kolumna, 1 - 2 kolumna, itd.
                response.id = sqlite3_column_int(stmt, 0);
                response.privilege = sqlite3_column_int(stmt, 1);
                response.login = (const char*)sqlite3_column_text(stmt, 2);
            }
        } else {
            response.found = false;
            cout << "Zapytanie wykonano pomyślnie, jednak nie znaleziono wiersza" << endl;
        }
    } else {
        prepStmtError();
    }

    return response;
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
