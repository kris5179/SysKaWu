#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <qtmetamacros.h>
#include "../backend/connection.h"

class Manager : public QObject {
    Q_OBJECT;
    Q_PROPERTY(QVariantMap returnUser, READ returnUser NOTIFY loginSignal);
    Connection con;
    queryResponse response;
    QVariantMap user;
public:
    Manager() {};
    // mapa to słownik klucz - wartość
    QVariantMap returnUser() { return user; } 
    Q_INVOKABLE void logIntoApp(string login, string password){
        response = con.Login(login, password);
        
        // response.id = -1, kiedy nie znaleziono usera, tak napisalem funkcje w connection.cpp
        // response.found == false jest wtedy, kiedy nie znaleziono użytkownika
        // a response.id < 0 wtedy, kiedy hasło jest złe
        if (response.found == false || response.id < 0){

            // nwm czemu akurat emit, no ale tak sie to robi w Qt
            emit loginSignal();
        }
        else {
            user["id"] = response.id;

            // przejscie ze stringa na QString
            user["login"] = QString::fromStdString(response.login);
            user["privilege"] = response.privilege;
            emit loginSignal(); 
        }
}
signals:
    void loginSignal();
};
