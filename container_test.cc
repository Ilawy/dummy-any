#include "container.cc"
#include "./cc_labs/lib/flex_stack.hh"
#include "iostream"
#include "cstring"

class Mina : printable
{

    void myCustomDestructor() {}
    int age;

public:
    Mina(int age)
    {
        this->age = age;
    };

    char *toString()
    {
        char *message = new char[30];
        strcpy(message, "Mina{\n  [native code]\n}");
        return message;
    }
};

using namespace std;

int main()
{

    try
    {
        FlexStack<container *> stack;
        container *age = new container(21.5f);
        cout << age << endl;
        delete age;
        age = new container(5);
        cout << age << endl;
        delete age;
        age = new container((char *)("Mohammed Amr"));
        cout << age << endl;
        delete age;
        age = new container(1024);

        container *name = new container((char *)("Mohammed Ali"));
        container *obj = new container(Mina(29));
        stack.push(age);
        stack.push(obj);
        stack.push(name);
        for (int i = 0; i < stack.getSize(); i++)
        {
            cout << stack[i] << endl;
        }
    }
    catch (const char *e)
    {
        cout << e;
    }

    return 0;
}