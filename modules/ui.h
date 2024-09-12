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

    while (((accNum < 1) || (choiceCondition))) // will exit loop when both- accNum and choice r valid
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
                return 0;
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

    return 0;


}

inline int action3sub1()
{
    int choice = -1;

    bool condition = !((choice> -1) && (choice < 5));

    while (condition)
    {
        cout << "\nAvailable actions are: " << endl;
        cout << "1) Deposit" << endl;
        cout << "2) Withdraw" << endl;
        cout << "3) Change account details" << endl;
        cout << "4) DELETE account" << endl;
        cout << "0) EXIT" << endl;
        cout << "Your choice: ";
        cin >> choice;

        condition = !((choice> -1) && (choice < 5));

        if (condition)
        {
            cout << "\nInvalid input: " << choice;
        }
        else
        {
            return choice;
        }
    }

    return -1;
}

inline void displayAddressStruct(AddressStruct addr)
{
    cout << "Pincode: " << addr.pincode << endl;
    cout << "City: " << addr.city << endl;
    cout << "State: " << addr.state << endl;
    cout << "Country: " << addr.country << endl;

}

inline int action3submenu3(int accNum)
{
    int choice = -1;
    string schoice;
    bool condition = !((choice>-1) && (choice<5));
    int c1;
    string c1type;
    AddressStruct addr;

    char c;

    while (condition)
    {
        cout << "Select attribute to modify:" << endl;
        cout << "1) Change account type (Current/Savings)" << endl;
        cout << "2) Change account holder name" << endl;
        cout << "3) Change account holder age" << endl;
        cout << "4) Change account holder address" << endl;
        cout << "0) EXIT" << endl;
        cout << "Your choice: " ;
        cin >> choice;

        condition = !((choice>-1) && (choice<5));

        if (condition)
        {
            cout << "Invalid input: " << choice << endl;
        }
        else
        {
            if (choice == 0)
            {
                verboseExit();
                condition = false;
                break;
                return 0;
            }

            switch (choice)
            {
            case 1:
                acc.dumpAccount();
                acc.pullAccount(accNum);
                cout << "The account is: " << endl << endl;
                acc.display();
                
                cout << "\nChange account type to: " << endl;
                cout << "1) Savings Account" << endl;
                cout << "2) Current Account" << endl;
                cout << "Your choice: " ;
                cin >> c1;

                if (c1 == 1)
                    c1type = "Savings Account";
                else if (c1 == 2)
                    c1type = "Current Account";
                


                if (c1==1 || c1==2)
                {
                    Account::updateAccountType(accNum, c1type);
                    acc.dumpAccount();
                    acc.pullAccount(accNum);
                    cout << "\nUpdated account is:" << endl << endl;
                    acc.display();
                    acc.dumpAccount();
                    condition = false;
                    verboseExit();
                    return 0;
                }

                else
                {
                    cout << "Invalid Input: " << c1 << endl;
                }
                break;

            case 2: // Change name
                acc.dumpAccount();
                acc.pullAccount(accNum);
                cout << "The account is: " << endl << endl;
                acc.display();
                
                cin.ignore();
                cout << "\nCurrent name on account: " << acc.getName() << endl;
                cout << "Enter new name: ";
                getline(cin, schoice);

                
                cout << "\nSelected name is :" << schoice << endl;
                cout << "Save changes? (y/n) : ";
                cin >> c;

                c = tolower(c);
                

                if (c == 'y')
                {
                    Account::updateName(accNum, schoice);
                    acc.dumpAccount();
                    acc.pullAccount(accNum);
                    cout << "\nUpdated account is:" << endl << endl;
                    acc.display();
                    acc.dumpAccount();
                    condition = false;
                    verboseExit();
                    return 0;
                }
                else
                {
                    condition = false;
                    verboseExit();
                    return 0;
                }
                break;

            case 3: // Change age
                acc.dumpAccount();
                acc.pullAccount(accNum);
                cout << "The account is: " << endl << endl;
                acc.display();
                
                c1 = 0;

                while (c1 < 1)
                {
                    cout << "\nCurrent age on account: " << acc.getAge() << endl;
                    cout << "Enter new age: ";
                    cin >> c1;

                    if (c1 < 1)
                    {
                        cout << "Invalid choice: " << c1 << endl;
                        cout << "Please enter valid age." << endl << endl;
                    }
                }

                
                cout << "\nSelected age is :" << c1 << endl;
                cout << "Save changes? (y/n) : ";
                cin >> c;

                c = tolower(c);
                

                if (c == 'y')
                {
                    Account::updateAge(accNum, c1);
                    acc.dumpAccount();
                    acc.pullAccount(accNum);
                    cout << "\nUpdated account is:" << endl << endl;
                    acc.display();
                    acc.dumpAccount();
                    condition = false;
                    verboseExit();
                    return 0;
                }
                else
                {
                    condition = false;
                    verboseExit();
                    return 0;
                }
                break;

            case 4: // Change address
                acc.dumpAccount();
                acc.pullAccount(accNum);
                cout << "The account is: " << endl << endl;
                acc.display();
                
                

                cout << endl << endl << "Current address is: " << endl;
                displayAddressStruct(acc.getAddress());

                cout << "\nEnter new address:" << endl;
                
                cout << "Pincode: ";
                cin >> addr.pincode;

                cout << "City: ";
                cin >> addr.city;

                cout << "State: ";
                cin >> addr.state;

                cout << "Country: ";
                cin >> addr.country;

                cout << "\n\nEntered address is :" << endl;
                displayAddressStruct(addr);

                cout << "\nSave changes? (y/n) : " ;
                cin >> c;

                c = tolower(c);
                

                if (c == 'y')
                {
                    Account::updateAddress(accNum, addr);
                    acc.dumpAccount();
                    acc.pullAccount(accNum);
                    cout << "\nUpdated account is:" << endl << endl;
                    acc.display();
                    acc.dumpAccount();
                    condition = false;
                    verboseExit();
                    return 0;
                }
                else
                {
                    condition = false;
                    verboseExit();
                    return 0;
                }
                break;
            
            default: // parent function wont allow this
                return 0;
                break;
            }
        }
    }

    return 0;
}


inline int action3(int accNum)
{
    bool flag = true;
    float amt = 0;

    if (accNum == 0)
    {
        return 0;
    }

    while (flag)
    {
        cout << endl;
        
        acc.dumpAccount();
        if (acc.pullAccount(accNum))
        {
            cout << "The account is: " << endl;
            acc.display();

        }
        else
        {
            cout << "Account no longer exists with Account Number: " << accNum << endl;
            flag = false;
            verboseExit();
            break;
        }

        switch (action3sub1())
        {
            case 0: // Exit
                flag = false;
                verboseExit();
                break;

            case 1: // Deposit
                cout << "Please enter amount to deposit: ";
                cin >> amt;
                Account::deposit(accNum, amt);
                amt = 0;
                break;

            case 2: // Withdraw
                cout << "Please enter amount to withdraw: ";
                cin >> amt;
                Account::withdraw(accNum, amt);
                amt = 0;
                break;

            case 3: // Change account details
                if (!action3submenu3(accNum))
                    flag = false;
                break;

            case 4: // Delete account
                Account::deleteAccount(accNum);
                break;

            default: // Not possible because action3sub1() wont allow it
                return -1;
                break;

        }
    }

    return 0;
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
            action3(menu3());
            break;

        default:    // Not possible because menu0() wont allow it
            return 0;
            break;

    }

    
    return 0;
}


#endif