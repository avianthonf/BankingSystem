#ifndef DB_H
#define DB_H

#include <iostream>
#include "sqlite3.h"


sqlite3 *DB;

int openDB()
{
    const char* dbName = "bank.db";

    // Open DB
    int exit = sqlite3_open(dbName, &DB);

    if (exit)
    {
        cerr << "Error opening database bank.db : " << sqlite3_errmsg(DB);
    }

    //int accountNumber, string accountType, 
    //double accountBalance, string name, int age, AddressStruct address
    // Create Tables
    string sql = "CREATE TABLE IF NOT EXISTS Accounts("
                "accountNumber INTEGER PRIMARY KEY AUTOINCREMENT,"
                "accountType TEXT  NOT NULL,"
                "accountBalance FLOAT NOT NULL,"
                "name TEXT NOT NULL,"
                "age INT NOT NULL,"
                "pincode INT NOT NULL,"
                "city  TEXT NOT NULL,"
                "state TEXT NOT NULL,"
                "country TEXT NOT NULL);";

    char *messageError;

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK)
    {
        cerr << "Error with database: " << messageError << endl;
        sqlite3_free(messageError);
    }

    return 0;

}


void closeDB()
{
    sqlite3_close(DB);
}




#endif