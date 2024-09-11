#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string.h>
#include <iomanip>
#include "person.h"
#include "db.h"


using namespace std;



class Account : public Person
{
    private:
        int accountNumber = -1;
        string accountType = "Savings Account";
        float accountBalance = 0;

        bool initNotRun = true;

        static bool dbNotOpen;

        static int modifyDB(int accNum, int attribute, string svalue = "", float fvalue = 0, int ivalue = 0);
        static int modifyDBAddress(int accNum, AddressStruct addr);

    public:
        void init(int accType, float balance, string n, int a, AddressStruct addr)
        {
            if (initNotRun)
            {   
                // Set acc type
                if (accType == 2)
                    accountType = "Current Account";

                // Acc balance
                accountBalance = balance;


                // set name , age, address
                Person::init(n, a, addr);

                // Set account as active
                // Make sure init() doesn't run again
                initNotRun = false;

                if (dbNotOpen)
                {
                    openDB();
                    dbNotOpen = false;
                }

                saveAccount();
                accountNumber= getDBAccNum();
                cout << "Account created successfully: " << endl;
                display();
            }
        }

        void initPull(int accNum, string accType, float balance, string n, int a, AddressStruct addr)
        {
            
                accountType = accType;

                // Acc balance
                accountBalance = balance;

                accountNumber = accNum;


                // set name , age, address
                Person::init(n, a, addr);

                // Set account as active
                // Make sure init() doesn't run again
                initNotRun = false;

            
        }

        ~Account()
        {
            if (!dbNotOpen)
            {
                closeDB();
            }
        }

        void display()
        {
            cout << endl;
            cout << "Account Number: " << accountNumber << endl;
            cout << "Account Type: " << accountType << endl;
            cout << "Name: " << name << endl;
            cout << fixed << setprecision(2);
            cout << "Account Balance: " << accountBalance << endl;
            cout << "Age: " << age << endl;
            cout << "Address: " << address.pincode << ", " << address.city << ", " << address.state << ", " << address.country << endl; 
        }

        // Getter methods
        int getAccountNumber() const { return accountNumber;}
        string getAccountType() const {return accountType;}
        float getAccountBalance() const {return accountBalance;}

        //Methods for account operation

        int deposit(float amount)
        {
            if (amount > 0)
            {
                accountBalance += amount;
                cout << "Deposit Successful. New balance: " << accountBalance << endl;
                return 0;
            }
            else
            {
                cerr << "Please enter POSITIVE value for deposit amount." << endl;
                return 1;
            }
        }

        int withdraw(float amount) // Returns 0 for success, -1 for insufficient balance, 1 for invalid input
        {
            if (amount > 0)
            {
                if (amount >= accountBalance)
                {
                    accountBalance -= amount;
                    cout << "Withdrawal successful. New balance: " << accountBalance << endl;
                    return 0;
                }
                else
                {
                    cerr << "ERROR: Insufficient funds in account." << endl;
                    cout << "Balance: " << accountBalance << ", Withrawal Request: " 
                    << amount << endl;
                    return -1;
                }
            }
            else
            {
                cerr << "ERROR: Please enter POSITIVE value for Withdrawal Amount." << endl;
                cout << "Entered value: " << amount << endl;
                return 1;
            }
        }


        void saveAccount()
        {
            string start = "INSERT INTO Accounts"
                                "( accountType, accountBalance, name, age,"
                                "pincode, city, state, country)"
                                "VALUES (";
                
            string sql;
            sql.reserve(1000);

             sql = start + "'" + accountType + "',"
                    + to_string(accountBalance) + ",'" + name + "'," + to_string(age)
                    + "," + to_string(address.pincode) + ",'" + address.city + "','" + address.state
                    + "','" + address.country + "');" ;

            char *messageError;
            int exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
            
            if (exit != SQLITE_OK)
            {
                cerr << "Error saving account: " << messageError << endl;
                sqlite3_free(messageError);
            }
        }

        void dumpAccount()
        {
            initNotRun = true;
            accountNumber = -1;

        }

        static int getDBAccNum();

        

        static void createAccounts(int n);
        bool pullAccount(int accNum);
        static void displayAllAccounts();
        static void deleteAccount(int accNum);


};

bool Account::dbNotOpen = true;

Account acc;

int Account::getDBAccNum()
{
    if (dbNotOpen)
        openDB();

    sqlite3_stmt *statement;
    const char* query = "SELECT accountNumber FROM Accounts ORDER BY accountNumber DESC LIMIT 1;";

    int returnCode;
    
    // Prepare query
    returnCode = sqlite3_prepare_v2(DB, query, -1, &statement, nullptr);
    if (returnCode != SQLITE_OK)
    {
        cerr << "Error occured with database: " << sqlite3_errmsg(DB) << endl;
        closeDB();
        dbNotOpen = true;
        return -1;
    }

    // Execute query
    returnCode = sqlite3_step(statement);
    if (returnCode == SQLITE_ROW)
    {
        int savedAccNum = sqlite3_column_int(statement, 0);
        return savedAccNum;
    }
    else 
    {
        return -1;
    }
    
    sqlite3_finalize(statement);
}

int Account::modifyDBAddress(int accNum, AddressStruct addr)
{
    if (dbNotOpen)
    {
        openDB();
        dbNotOpen = false;
    }

    string sql[3];

    sql[0] = "UPDATE Accounts SET pincode = ? WHERE accountNumber = ?;";
    sql[1] = "UPDATE Accounts SET city = ? WHERE accountNumber = ?;";
    sql[2] = "UPDATE Accounts SET state = ? WHERE accountNumber = ?;";

    sqlite3_stmt* statement[3];

    int rc[3];

    for (int i=0; i<3; i++)
    {
        rc[i] = sqlite3_prepare_v2(DB, sql[i].c_str(), -1, &statement[i], nullptr);

        if (rc[i] != SQLITE_OK)
        {
            cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
            return -1;
        }
    }

    for (int i=0; i < 3; i++)
    {
        sqlite3_bind_int(statement[i], 2, accNum);
    }

    sqlite3_bind_int(statement[0], 1, addr.pincode);
    sqlite3_bind_text(statement[1], 1, addr.city.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(statement[2], 1, addr.state.c_str(), -1, SQLITE_STATIC);

    for (int i=0; i < 3; i++)
    {
        rc[i] = sqlite3_step(statement[i]);

        if (rc[i] != SQLITE_DONE)
        {
            cerr << "Execution failed: " << sqlite3_errmsg(DB) << endl;
            return -1;
        }
    }

    for (int i=0; i < 3; i++)
    {
        sqlite3_finalize(statement[i]);
    }


    return 0;
}

int Account::modifyDB(int accNum, int attribute, string svalue, float fvalue, int ivalue)
{
    if (dbNotOpen)
    {
        openDB();
        dbNotOpen = false;
    }

    string sql = "UPDATE Accounts SET ";

    sqlite3_stmt *statement;


    switch (attribute)
    {
    case 1: // Account type
        sql.append("accountType = ? WHERE ");
        break;

    case 2: // Balance
        sql.append("accountBalance = ? WHERE ");
        break;

    case 3: // Name
        sql.append("name = ? WHERE ");
        break;

    case 4: // Age
        sql.append("age = ? WHERE ");
        break;
    
    default:
        return 0;
        break;
    }

    sql.append("accountNumber = ?;");

    
    int returnCode;

    returnCode = sqlite3_prepare_v2(DB, sql.c_str(), -1, &statement, nullptr);
    if (returnCode != SQLITE_OK)
    {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(DB) << endl;
        return -1;
    }

    // values to bind

    sqlite3_bind_int(statement, 2, accNum);

    svalue = "'" + svalue + "'";
    
    switch (attribute)
    {
    case 1: // Account type
        sqlite3_bind_text(statement, 1, svalue.c_str(), -1, SQLITE_STATIC);
        break;

    case 2: // Balance
        sqlite3_bind_double(statement, 1, fvalue);
        break;

    case 3: // Name
        sqlite3_bind_text(statement, 1, svalue.c_str(), -1, SQLITE_STATIC);
        break;

    case 4: // Age
        sqlite3_bind_int(statement, 1, ivalue);
        break;
    
    default:
        return 0;
        break;
    }


    returnCode =  sqlite3_step(statement);

    if (returnCode == SQLITE_DONE)
    {
        return 0;
    }
    else
    {
        cerr << "Execution of sql failed: " << sqlite3_errmsg(DB) << endl;
        return -1;
    }




    return -1;

}

void Account::createAccounts(int n)
{
    
        // Account attributes
    int accountNumber; 
    string accountType; int accountTypeInt = 1; 
    double accountBalance; 
    string name;
    int age; 
    AddressStruct address;

    acc.dumpAccount();

    // Get user input and create accounts

    for (int i=0; i<n; i++)
    {
        cout << "Creating account " << i+1 << " of " << n << "..." << endl;

        cout << "Choose Account Type:" << endl;
        cout << "1) SAVINGS Account" << endl;
        cout << "2) CURRENT Account" << endl;
        cout << "Your choice: " ;
        cin >> accountTypeInt; // Will be used later
        

        cout << "Enter Account Balance: ";
        cin >> accountBalance;


        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Address:" << endl;
        cout << "\tState: ";
        cin >> address.state;
        cout << "\tCity: ";
        cin >> address.city;
        cout << "\tPincode: ";
        cin >> address.pincode;

        
        acc.init(accountTypeInt, accountBalance, name, age, address);
        acc.dumpAccount();
    }
    
}

bool Account::pullAccount(int accNum)
{
    if (Account::dbNotOpen)
    {
        openDB();
        dbNotOpen = false;

    }

    dumpAccount();

    int returnCode;
    sqlite3_stmt *statement;
    string query = "SELECT * FROM Accounts WHERE accountNumber = " + to_string(accNum) + ";";

    // Prepare the sql query
    returnCode = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);
    if (returnCode != SQLITE_OK)
    {
        cerr << "Failed to access database: " << sqlite3_errmsg(DB) << endl;
        closeDB();
        Account::dbNotOpen = true;
        return false;
    }


    // int accNum, int accType, float balance, string n, int a, AddressStruct addr
    while ((returnCode = sqlite3_step(statement)) == SQLITE_ROW)
    {

        int accNum = sqlite3_column_int(statement, 0);
        string accType = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 1)));
        float balance = static_cast<float>(sqlite3_column_double(statement, 2));
        string name = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 3)));
        int age = sqlite3_column_int(statement, 4);


        AddressStruct addr;

        addr.pincode = sqlite3_column_int(statement, 5);


        addr.city = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 6)));
        addr.state = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 7)));
        addr.country = string(reinterpret_cast<const char*>(sqlite3_column_text(statement, 8)));

        initPull(accNum, accType, balance, name, age, addr);

    }

    if (returnCode != SQLITE_DONE)
    {
        cerr << "Error while handling data" << endl;
    }

    sqlite3_finalize(statement);

    if (accountNumber == -1)
    {
        dumpAccount();
        return false;
    }
    else 
        return true;

}

void Account::displayAllAccounts()
{
    if (dbNotOpen)
    {
        openDB();
        dbNotOpen = false;
    }

    int first=1, last= getDBAccNum();

    for (int i=first; i <= last; i++)
    {
        acc.pullAccount(i);
        
        if (acc.accountNumber != -1)
        {
            acc.display();
        }

        acc.dumpAccount();
    }

}

void Account::deleteAccount(int accNum)
{
    if (dbNotOpen)
    {
        openDB();
        dbNotOpen = false;
    }

    acc.dumpAccount();

    acc.pullAccount(accNum);

    if (acc.accountNumber == -1)
    {
        cerr << "Account does not exist with Account Number: " << accNum << endl;
        cout << "Failed to delete." << endl;
    }
    else
    {
        char choice;
        cout << "Found Account: " << endl;
        acc.display();
        cout << "Do you wish to delete? (y/n) :";
        cin >> choice;

        choice = tolower(choice);

        if (choice == 'y')
        {
            // Delete account
            sqlite3_stmt *statement;
            string query = "DELETE FROM Accounts WHERE accountNumber = " + to_string(accNum) + ";";

            int returnCode;

            returnCode = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);
            if (returnCode != SQLITE_OK)
            {
                cerr << "Failed to delete: " << sqlite3_errmsg(DB) << endl;
            }

            returnCode = sqlite3_step(statement);

            if (returnCode == SQLITE_DONE)
            {
                cout << "Account deleted successfully." << endl;
            }
            else
            {
                cerr << "Error deleting account: " << sqlite3_errmsg(DB) << endl;
            }

        }
        
        
        
        
    }

    acc.dumpAccount();
    

}



#endif