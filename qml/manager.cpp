#include "manager.h"
using namespace std;

Manager::Manager() {};

// mapa to słownik klucz - wartość
QVariantMap Manager::getUser() {
    return user; 
} 

Q_INVOKABLE void Manager::logIntoApp(QString login, QString password){
    response = con.Login(login.toStdString(), password.toStdString());
    
    // response.found == false jest wtedy, kiedy nie znaleziono użytkownika
    if (response.found == false) {
        loginSuccess = false;
        emit loginSignal();
    }

    // response.id = -1, kiedy hasło jest złe
    else if (response.id < 0){
        loginSuccess = false;
        emit loginSignal();
    }
    else {
        loginSuccess = true;
        user["id"] = response.id;

        // przejscie ze stringa na QString
        user["login"] = QString::fromStdString(response.login);
        user["privilege"] = response.privilege;
        emit loginSignal(); 
    }
}
Manager::~Manager() {};
