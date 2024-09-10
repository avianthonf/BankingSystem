#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string.h>
#include "person.h"
#include "db.h"


using namespace std;

class Account : public Person
{
    private:
        int accountNumber = 0;
        string accountType = "Savings Account";
        float accountBalance = 0;

        bool initNotRun = true;

        bool dbNotOpen = true;


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
            }
        }

        ~Account()
        {
            if (!dbNotOpen)
            {
                closeDB();
            }
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

        // to implement
        int deleteAccount()
        {
            return 0;
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

        }

        static void createAccounts(int n);


};

Account acc;

void Account::createAccounts(int n)
{
    
        // Account attributes
    int accountNumber; 
    string accountType; int accountTypeInt = 1; 
    double accountBalance; 
    string name;
    int age; 
    AddressStruct address;

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
        cin.ignore();
        cout << "\tState: ";
        getline(cin, address.state);
        cin.ignore();
        cout << "\tCity: ";
        getline(cin, address.city);
        cout << "\tPincode: ";
        cin >> address.pincode;

        acc.dumpAccount();
        acc.init(accountTypeInt, accountBalance, name, age, address);
    }
    
}



#endif