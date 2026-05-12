#include <iostream>
#include "backend/serverHeader.h"
#include "qml/manager.h"
#include "backend/passwords.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <sodium.h>
#include <sodium/core.h>
#include <sodium/crypto_generichash.h>
#include <sodium/crypto_pwhash.h>
#include <sodium/crypto_secretbox.h>
#include <sodium/randombytes.h>
// #include "manager.h"

using namespace std;

int main(int argc, char* argv[]){
    // inicjalizacja libsodium  
    if (sodium_init() < 0){
        cout << "Biblioteka sodium nie mogła zostać załadowana" << endl;
    }
    
    Connection con = Connection();
    string haslo = "haslo";
    string login = "login";
    string hash = passHashing(haslo);
    con.Insert(1, 2, login, hash);
    
    Manager manager;
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.load("qrc:/main.qml");
    engine.rootContext()->setContextProperty("klinika", &manager);
    return app.exec();

    //Server Server(8080);
    //if (!Server.start()) {
    //    return 1;
    //}
    //Server.run();
    //return 0;
}
