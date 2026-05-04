#include <iostream>
#include "backend/serverHeader.h"
#include "backend/connection.h"
#include "backend/szyfrowanie.h"

using namespace std;

int main(){

    Server Server(8080);

    if (!Server.start()) {
        return 1;
    }

    Server.run();
    return 0;

}
