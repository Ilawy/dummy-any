#include <typeinfo>
#include <iostream>
#include <cstring>
#include "libany.hh"

using namespace std;

template <typename Derived, typename Base>
bool isDerivedFrom()
{
    return typeid(Derived).before(typeid(Base));
}

class Dummy
{

public:
    int age = 75;
    int pwd = 5;

    ~Dummy()
    {
        cout << "dummy died";
    }
};

void free_dummy(void *ptr)
{
    delete (Dummy *)ptr;
}

class StackOfAny
{
    Any **items;
    int size;
    int top;

public:
    StackOfAny(int size = 64)
    {
        this->size = size;
        this->top = 0;
        this->items = new Any *[size];
    }

    void push(Any &item)
    {
        if (this->top >= this->size)
            throw "lol";
        this->items[top++] = &item;
    }

    Any &at(int index)
    {
        // if(index < 0)throw "out of bound";
        // if(index >= top)throw "out of bound";
        return *this->items[index];
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
        Any age = 24;
        Any salary = (float)39.4f;
        Any kids = 3;
        Any random = new Dummy();
        random.free0 = free_dummy;

        StackOfAny s;
        s.push(age);
        s.push(salary);
        s.push(kids);
        s.push(random);

        cout << s.at(0).as<int>() << endl;
        cout << s.at(1).as<float>() << endl;
        cout << s.at(2).as<int>() << endl;
        cout << s.at(3).as<Dummy *>()->age << endl;
    }
    catch (const char *e)
    {
        cout << "ERROR: " << e;
    }
}