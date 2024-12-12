#include "typeinfo"
#include "utility"
#include <iostream>

typedef void *(*CopyFn)(void *);
typedef void (*DelFn)(void *);

class printable
{
public:
    virtual char *toString() = 0;
};

class container
{
    std::type_info const &info;
    void *value;
    CopyFn _copy_ = nullptr;
    DelFn _free_ = nullptr;

public:
    template <typename T>
    container(T &&value)
        : value{new T{std::forward<T>(value)}}, info{typeid(T)}
    {
    }

    template <typename T>
    container(T &&value, CopyFn copy, DelFn free)

        : value{new T{std::forward<T>(value)}}, info{typeid(T)}, _copy_(copy), _free_(free)

    {
    }

    container(container const &original) : info(original.info)
    {
        if (_copy_ == nullptr)
            throw "Cannot copy without copy fn";
        this->value = original._copy_(original.value);
        this->_copy_ = original._copy_;
    }

    template <typename T>
    T &as()
    {
        return *(T *)(value);
    }

    template <typename T>
    bool is()
    {
        return typeid(T) == info;
    }

    template <typename T>
    bool isBaseOf()
    {
        return info.before(typeid(T));
    }

    std::type_info const &type()
    {
        return info;
    }

    ~container()
    {
        if (this->_free_ != nullptr)
        {
            this->_free_(this->value);
        }
    }

    // friend std::ostream& operator<<(std::ostream& os, const container& obj) {
    //     std::cout << obj.info.before(typeid(printalbe)) << std::endl;
    //     // os << obj.val;
    //     return os;
    // }

    friend std::ostream &operator<<(std::ostream &os, container *obj)
    {
        if (typeid(int) == obj->info)
        {
            os << *(int *)obj->value;
        }
        else if (typeid(float) == obj->info)
        {
            os << *(float *)obj->value;
        }
        else if (typeid(char *) == obj->info)
        {
            os << *(char **)obj->value;
        }
        else if (obj->info.before(typeid(printable)))
        {
            if (obj->info.__is_pointer_p())
            {
                printable *p = *(printable **)obj->value;
                os << p->toString();
            }
            else
            {
                os << (*(printable *)obj->value).toString();
            }
        }
        else
        {
            os << obj->value;
        }
        return os;
    }
};