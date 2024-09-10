#include <iostream>

#include "modules/account.h"
#include "modules/structs.h"

using namespace std;

int main()
{
    int x;
    cout << "Acc num: " ;
    cin >> x;
    Account::deleteAccount(x);

    Account::displayAllAccounts();

}