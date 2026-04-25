#include <iostream>
#include "sqlite3.h"
#include "szyfrowanie.h"
#include "db_test.h"
#include "connection.h"

using namespace std;

int main()
{
    sqlite3 *db=nullptr;
    int rc=0;
    int testId=7;
    string testPassword="qwerty";
    string testHash=test(testPassword);
    
    Connection baza(rc, db, "example_users");
    baza.SelectById(6);
    baza.SelectByLogin("user");
    baza.SelectByPrivilege(7);
    baza.Delete(8);
    baza.Delete("user");
}
