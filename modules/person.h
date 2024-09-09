#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include "structs.h"
using namespace std;


class Person
{
    protected:
        void init(string name, int age, AddressStruct address)
        {
            Person::name = name;
            Person::age = age;
            Person::address = address;

        }

        string name = "NULL";
        int age = 0;
        AddressStruct address;


    public:
    string getName() const {return name;}
    int getAge() const {return age;}
    AddressStruct getAddress() const {return address;}

};


#endif