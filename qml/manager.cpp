#include "manager.h"
#include <qcontainerfwd.h>
#include "../backend/queryResponse.h"
#include <iostream>
using namespace std;

Manager::Manager() {};

// mapa to słownik klucz - wartość
QVariantMap Manager::getUser() {
    return user; 
} 

Q_INVOKABLE void Manager::logIntoApp(QString login, QString password){
    response = con.Login(login.toStdString(), password.toStdString());
    
    // response.found == false jest wtedy, kiedy nie znaleziono użytkownika
    if (response.found == false || response.id < 0) {
        if (response.found == false) cerr << "Nie znaleziono użytkownika w bazie" << endl;
        if (response.id < 0)         cerr << "Hasło użytkownika się nie zgadza" << endl;
        loginSuccess = false;
        user["errMsg"] = QString("Błędny login lub hasło");
        emit loginSignal();
    } else {
        loginSuccess = true;
        user["id"] = response.id;
        // przejscie ze stringa na QString
        user["login"] = QString::fromStdString(response.login);
        user["privilege"] = response.privilege;
        emit loginSignal(); 
    }
}

QVariantList Manager::getAnimals(int id){
    QVariantList result;
    for (const animal& a : con.getAnimals(id)){
        QVariantMap map;
        map["id"]           = a.id;
        map["species"]      = a.species;
        map["breed"]        = a.breed;
        map["name"]         = a.name;
        map["ownerId"]      = a.ownerId;
        map["reason"]       = a.reason;
        result.append(map);
    }
    return result;
} 

Manager::~Manager() {};
