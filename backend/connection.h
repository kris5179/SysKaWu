#include <string>
#include "sqlite3.h"
#include "queryResponse.h"
using namespace std;


class Connection {
private:
    sqlite3* dbHandle_;
    string filename_;
public:
    Connection(const string& filename = "Baza_glowna.db");
    virtual ~Connection();
    void Insert(int id, int privilege, const string& username, const string& password);
    void SelectById(int id);
    void SelectByPrivilege(int privilege);
    void Delete(int id);
    void Delete(string username);
    queryResponse Login(string login, string password);
    void queryError();
    void prepStmtError();
};
