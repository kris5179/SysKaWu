#pragma once
#include <string>
#include <QObject>
using namespace std;

struct queryResponse {
    int privilege;
    bool found;
    int id;
    string login;
};

struct animal {
    int id;
    QString species;
    QString breed;
    QString name;
    int ownerId;
    QString reason;
};
