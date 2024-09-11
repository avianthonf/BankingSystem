#include <iostream>

#include "modules/ui.h"


using namespace std;

int main()
{
    do
    {
        ui();
    } while (readRestartFlag());

}