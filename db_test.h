#pragma once
#include <string>
#include "sqlite3.h"
using namespace std;

int databaseConnection(sqlite3* &db, string filename);
void databasePasswordEntry(sqlite3* &db, const char* password);
