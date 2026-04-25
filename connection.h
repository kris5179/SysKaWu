#include <string>
#include "sqlite3.h"
using namespace std;


class Connection {
private:
    int rc_;
    sqlite3* dbHandle_;
    string filename_;
public:
    Connection();
    Connection(int rc, sqlite3* &dbHandle, string filename);
    virtual ~Connection();
    void Insert(int id, int privilege, string username, string password);
    void SelectById(int id);
    void SelectByPrivilege(int privilege);
    void SelectByLogin(string username);
    void Delete(int id);
    void Delete(string username);
};

