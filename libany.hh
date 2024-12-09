#include <iostream>
using namespace std;

struct Any
{
    void *data_;
    std::type_info const &type_;

    Any() : type_(typeid((int)1))
    {
    }

    template <typename T>
    explicit Any(T &&value)
        : data_{new T{std::forward<T>(value)}}, type_{typeid(T)}
    {
    }


    int to_int(){
        return **(int**)this->data_;
    }

    float to_float(){
        return **(float**)this->data_;
    }
};