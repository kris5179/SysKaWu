#include <iostream>
#include "sqlite3.h"
#include "szyfrowanie.h"
#include "db_test.h"


using namespace std;

int main()
{
    sqlite3 *db = nullptr;
    string testoweHaslo = "qwerty";
    string zahashowane = test(testoweHaslo);
    int con = databaseConnection(db, "example_users.db");
    databasePasswordEntry(db, zahashowane.c_str());
}
