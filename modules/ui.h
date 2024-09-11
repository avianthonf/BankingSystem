#ifndef UI_H
#define UI_H

#include <iostream>
#include "account.h"

using namespace std;

bool restartFlag = false;

// if var is true, returns true and changes var to false; else returns false
bool readRestartFlag() 
{
    if (restartFlag)
    {
        restartFlag = false;
        return true;
    }
    else
    {
        return false;
    }

}

int verboseExit()
{
    char c1;
    cout << "\nDo you want to go back to the main menu? (y/n) : ";
    cin >> c1;
    c1 = tolower(c1);

    if (c1 == 'y')
    {
        restartFlag = true;
        cout << "Restarting..." << endl;
        return 0;
    }
    else
    {
        cout << "Exiting..." << endl;
        return 0;
    }
}

inline int menu0()
{
    int choice = -1;
    bool condition = (!((choice > -1) && (choice < 4)));
    while (condition) // while invalid input
    {

        cout << "Choose action to perform:" << endl;
        cout << "1) Create new accounts" << endl;
        cout << "2) Display all accounts" << endl;
        cout << "3) Modify / Delete existing account" << endl;
        cout << "0) EXIT" << endl;
        cout << "Your choice: ";
        cin >> choice;



        condition = (!((choice > -1) && (choice < 4)));
        if (condition)
        {
            cout << "\nInvalid input: " << choice << endl;
            cout << "Please enter valid input\n" << endl;
        }
        else
            return choice;
    }
    return 0;
}

inline int menu1() // Create accounts (input)
{
    int choice = -1;

    while (choice < 0)
    {
        cout << "\nNOTE: Enter 0 to cancel account creation." << endl;
        cout << "Enter number of accounts to create: ";
        cin >> choice;

        if (choice < 0)
        {
            cout << "\nInvalid input: " << choice << endl;
            cout << "Please enter non-negative value" << endl << endl;
        }
        else
            return choice;

        
    }

    return 0;
}

inline int action1(int choice) // Create accounts (action)
{
    if (choice == 0)
    {
        cout << "Opening main menu..." << endl;
        restartFlag = true;
        return 0;
    }
    else
    {
        Account::createAccounts(choice);

        cout << "Successfully created and saved accounts." << endl;
        
        verboseExit();

        return 0;

    }

    return -1;
}

inline int action2() // Display all accounts (action only)
{
    cout << endl;

    Account::displayAllAccounts();

    verboseExit();

    return 0;

}

inline int menu3() // Helps you select the account number for the action
{
    int accNum = -1;
    int choice = -1;
    int tempAccNum;

    bool choiceCondition = !((choice<3) && (choice>-1));

    while ((accNum < 1) || (choiceCondition)) // will exit loop when both- accNum and choice r valid
    {
        cout << "\nSelect account number to perform action on," << endl;
        cout << "1) Display All Accounts" << endl;
        cout << "2) Enter Account Number (Selected Account will be displayed before selecting)" << endl;
        cout << "0) EXIT" << endl;
        cout << "Your choice: "; 
        cin >> choice;

        switch (choice)
        {
            case 0:
                verboseExit();
                break;

            case 1:
                Account::displayAllAccounts();
                cout << endl;
                break;

            case 2:
                cout << "Enter account number: ";
                cin >> tempAccNum;
                if (tempAccNum > 0)
                {
                    acc.dumpAccount();
                    acc.pullAccount(tempAccNum);
                    
                    if (acc.getAccountNumber() == -1)
                    {
                        cout << "\nAccount DOES NOT EXIST with account number: " << tempAccNum << endl;
                        acc.dumpAccount(); 
                    }
                    else
                    {
                        cout << "\nSelected account is: " << endl;
                        acc.display();

                        char c1;
                        cout << "\nDo you want to select this account? (y/n) : ";
                        cin >> c1;

                        c1 = tolower(c1);

                        if (c1 == 'y')
                        {
                            accNum = tempAccNum;
                            return accNum;
                        }
                    }
                }
                break;

                default:
                    cout << "\nInvalid input: " << choice << endl;
                    break;
        }


    }

    return -1;

}

inline void welcome0()
{
    cout << "Welcome to the Banking System" << endl;
    cout << "Written purely in C++ with SQLite3 C library" << endl; 
    cout << "GitHub: https://github.com/avianthonf/BankingSystem.git" << endl;
    cout << endl;
}


int ui()
{
    // greet
    welcome0();

    // First menu
    switch (menu0())
    {
        case 0:
            return 0;
            break;
        
        case 1: // Create new accounts
            action1(menu1());
            break;

        case 2: // Display all accounts
            action2();
            break;

        case 3: // Modify / delete existing account
            menu3();
            break;

        default:    // Not possible because menu0() wont allow it
            return 0;
            break;

    }

    
    return 0;
}


#endif