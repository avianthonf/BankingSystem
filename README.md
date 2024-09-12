**Banking System in C++**
This project implements a simple banking system in C++ using the SQLite3 database. It allows users to create accounts, modify account details, perform transactions (deposit/withdraw), and manage account records. The system uses a modular approach with separate components for the user interface (UI), database management, account handling, person information, and address structuring.

Features
Account Creation: Create new accounts with details like name, age, account type, and address.
Account Management: Modify or delete existing accounts, including changing details like the account holder's name, age, and address.
Transactions: Perform deposit and withdrawal operations on accounts.
Display Accounts: View all existing accounts.
SQLite3 Integration: Account information is stored and managed using SQLite3.
Files
main.cpp
The entry point of the application. It continuously calls the ui() function from the ui.h module to handle user interactions until the user decides to exit.

ui.h
Handles the user interface and provides options to:

Create new accounts.
Display all accounts.
Modify or delete existing accounts.
Deposit or withdraw from accounts.
Change account details such as name, age, address, or account type.
Exit the program.
db.h
Manages database operations, including:

Opening and closing the SQLite3 database.
Creating necessary tables if they do not exist.
person.h
Defines the Person class, which includes attributes for the person's name, age, and address, along with methods to access these attributes.

structs.h
Contains the AddressStruct structure used to represent an address, including attributes for the pincode, country, state, and city.

account.h
Defines the Account class with methods for:

Creating new accounts.
Displaying account details.
Updating account information such as type, name, age, and address.
Performing transactions like deposits and withdrawals.
Deleting accounts.
Methods include createAccounts(), displayAllAccounts(), updateAccountType(), updateName(), updateAge(), updateAddress(), deposit(), withdraw(), and deleteAccount().
