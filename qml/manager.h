#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>
#include <qtmetamacros.h>
#include "../backend/connection.h"

class Manager : public QObject {
    Q_OBJECT;
    Q_PROPERTY(QVariantMap user READ getUser NOTIFY loginSignal);
    Q_PROPERTY(bool loginSuccess READ getLoginSuccess NOTIFY loginSignal)
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
signals:
    void loginSignal();
};
