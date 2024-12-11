#include <iostream>
using namespace std;

class Any
{
    void *data_;
    std::type_info const &type_;

public:
    void (*free0)(void *data);

    Any() : type_(typeid((int)1))
    {
        this->free0 = nullptr;
    }

    template <typename T>
    Any(T &&value)
        : data_{new T{std::forward<T>(value)}}, type_{typeid(T)}
    {
        this->free0 = nullptr;
    }

    Any(void *data, std::type_info &info)
        : type_{info}
    {
        this->data_ = new void *;
    }

    ~Any()
    {
        if (this->free0 != nullptr)
        {
            this->free0(data_);
        }
        // else
        // {
        //     // WARNING UNDEFINED BEHAVIOUR
        //     if (type_.__is_pointer_p())
        //     {
        //         delete *(void **)data_;
        //     }
        //     else
        //         delete data_;
        // }
    }

    template <typename A>
    bool is_a()
    {
        return typeid(A) == this->type_;
    }

    template <typename A>
    A &as()
    {
        if (this->is_a<A>())
        {
            return *(A *)(this->data_);
        }
        throw "cannot cast";
    }
};