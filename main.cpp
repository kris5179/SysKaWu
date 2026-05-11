#include <iostream>
#include "backend/serverHeader.h"
#include "qml/manager.h"
#include "backend/connection.h"
#include "backend/szyfrowanie.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
// #include "manager.h"

using namespace std;

int main(int argc, char* argv[]){

    
    Connection con = Connection("example_users.db");
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
