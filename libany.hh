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


   
    template <typename A>
    bool is_a(){
        return typeid(A*) == this->type_;
    }

    template <typename A>
    A& as(){
        if(this->is_a<A>()){
            // void * val = this->data_;
            return **(A**)(this->data_);
        }
        throw "cannot cast";
    }
};