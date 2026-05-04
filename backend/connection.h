#include <string>
#include "sqlite3.h"
using namespace std;


class Connection {
private:
    sqlite3* dbHandle_;
    string filename_;
public:
    Connection();
    Connection(const string& filename);
    virtual ~Connection();
    void Insert(int id, int privilege, const string& username, const string& password);
    void SelectById(int id);
    void SelectByPrivilege(int privilege);
    void SelectByLogin(string username);
    void Delete(int id);
    void Delete(string username);
    void queryError();
    void prepStmtError();
};
