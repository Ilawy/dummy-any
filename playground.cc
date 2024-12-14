#include "iostream"
#include "cstring"
#include "container.hh"
#include "./cc_labs/lab_3/str.hh"
#include "./cc_labs/lib/flex_stack.hh"
#include <type_traits>
#include <typeinfo>
#include <cstring>
#include <memory>

using namespace std;

class Mina : public corem::printable
{
    int age;

public:
    char *oops;
    Mina()
    {
        cout << "CALLED MINA" << endl;
        this->oops = new char[30];
        strcpy(this->oops, "Hello");
    }
    Mina(Mina &other)
    {
        cout << "--- MINA ENTERED MEMORY ---" << endl;
        this->oops = new char[30];
        strcpy(this->oops, other.oops);
    }
    Mina(Mina &&other)
    {
        this->oops = new char[30];
        strcpy(this->oops, other.oops);
    }

    ~Mina(){
        cout << "--- MINA LEFT MEMORY ---" << endl;
        delete []oops;
    }

    void operator=(const Mina &other)
    {
        if (this != &other)
        {
            this->oops = new char[30];
            strcpy(this->oops, other.oops);
        }
    }

    char *toString()
    {
        char *value = new char[25];
        strcpy(value, this->oops);
        return value;
    }
};

class Mo
{
public:
    virtual ~Mo() {}
};

int main()
{

    FlexStack<Extra> s;
    s.push(Extra(3));
    s.push(Extra(2.25f));
    s.push(Extra("Human vs. alien"));
    // s.push(String("Hello world"));

    Mina m = Mina();
    s.push(m);
    strcpy(m.oops, "Modified oops");
    
    for(int i = 0; i < s.getSize(); i++){
        cout << s[i] << endl;
    }
    cout << m.oops << endl;

    return 0;
}