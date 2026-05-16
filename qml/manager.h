#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <qcontainerfwd.h>
#include <qtmetamacros.h>
#include "../backend/connection.h"

class Manager : public QObject {
    Q_OBJECT;
    Q_PROPERTY(QVariantMap user READ getUser NOTIFY loginSignal);
    Q_PROPERTY(bool loginSuccess READ getLoginSuccess NOTIFY loginSignal);
    Connection con;
    queryResponse response;
    QVariantMap user;
    bool loginSuccess = false;
public:
    Manager();
    virtual ~Manager();
    // mapa to słownik klucz - wartość
    QVariantMap getUser();
    Q_INVOKABLE void logIntoApp(QString login, QString password);
    bool getLoginSuccess() { return loginSuccess; }
    Q_INVOKABLE QVariantList getAnimals(int id);
    Q_INVOKABLE QVariantList getMedicines();
    Q_INVOKABLE void deleteMedicine(int id);
    Q_INVOKABLE void addMedicine(QString name, int stock, QString batchNumber, QString unit);
signals:
    void loginSignal();
};
