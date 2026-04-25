#include "connection.h"
#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

Connection::Connection(int rc,sqlite3* &dbHandle, string filename)
      : rc_(rc), dbHandle_(dbHandle), filename_(filename)
{
    //rc_ = sqlite3_open(filename_.c_str(), &dbHandle_);

    //if (rc_ != SQLITE_OK){
    //    cerr << "Błąd otwierania bazy danych" << endl;
    //} else {
    //    cout << "Baza danych otwarta pomyślnie" << endl;
    //}
    
    cout << "Hello, Connection" << endl;
}

void Connection::Insert(int id, int privilege, string username, string password){
    cout << "Hello, Insert" << endl;
}

void Connection::SelectById(int id){
    cout << "Hello, SelectById" << endl;
}

void Connection::SelectByPrivilege(int privilege){
    cout << "Hello, SelectByPrivilege" << endl;
}

void Connection::SelectByLogin(string username){
    cout << "Hello, SelectByLogin" << endl;
}

void Connection::Delete(int id){
    cout << "Hello, (id)Delete" << endl;
}

void Connection::Delete(string username){
    cout << "Hello (username)Delete" << endl;
}

Connection::~Connection(){
    cout << "Zniszczylem obiekt Connection" << endl;
}
