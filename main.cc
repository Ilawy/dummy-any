#include <typeinfo>
#include <iostream>
#include <cstring>
#include "libany.hh"

using namespace std;

char *getTypeId() {}

class StackOfAny
{
    Any **items;
    int size;
    int top;

public:
    StackOfAny(int size = 64) {
        this->size = size;
        this->top = 0;
        this->items = new Any*[size];
    }

    void push(Any *item)
    {
        if (this->top >= this->size)
            throw "lol";
        this->items[top++] = item;
    }

    Any *at(int index)
    {
        // if(index < 0)throw "out of bound";
        // if(index >= top)throw "out of bound";
        return this->items[index];
    }

    int length()
    {
        return this->top;
    }
};





int main()
{
    try
    {
        int myAge = 24;
        float mySalary = 250.75;
        Any age = Any(&myAge);
        Any salary = Any(&mySalary);
        // Any age = 10;
        StackOfAny s;
        s.push(&age);
        s.push(&salary);

        for (int i = 0; i < s.length(); i++)
        {
            Any *current = s.at(i);
            // cout << typeid(float*).name() << endl;
            // cout << typeid(int*).name() << endl;
            if(strcmp(current->type_.name(), typeid((float*)1).name()) == 0){
                cout << "My float is " << current->to_float() << endl; 
            }
            if(strcmp(current->type_.name(), typeid((int*)1).name()) == 0){
                cout << "My int is " << current->to_int() << endl; 
            }
        }
    }
    catch (const char *e)
    {
        cout << "ERROR: " <<  e;
    }
}