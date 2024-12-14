#include <typeinfo>
#include <iostream>

typedef void *(*CopyFn)(void *);
typedef void (*DelFn)(void *);

bool isDerivedFrom(const std::type_info &derived, const std::type_info &base)
{
    return derived.before(base);
}

using namespace std;

namespace corem
{
    class printable
    {
    public:
        virtual char *toString() = 0;
    };

    class copyable
    {
    public:
        virtual void *__copy__(void *) = 0;
    };
} // namespace corem

class Extra
{
private:
    const std::type_info *info;
    std::size_t size;
    bool can_print;
    bool can_copy;
    void *value;

public:
    Extra() : info(&typeid(void)), size(0), value(nullptr), can_print(false), can_copy(false) {}

    template <typename T>
    Extra(T x) : value{new T(std::move(x))}, info(&typeid(T)), size(sizeof(T)), can_print(std::is_base_of<corem::printable, T>::value), can_copy(std::is_base_of<corem::copyable, T>::value)
    {
    }

    Extra(const Extra &other) : info(other.info),
                                size(other.size),
                                can_copy(other.can_copy),
                                can_print(other.can_print),
                                // value(other.clone_(other.value)),
                                value(other.value)
    {
    }

    Extra &operator=(const Extra &other)
    {
        if (this != &other)
        {
            info = other.info;
            value = other.value;
            can_copy = other.can_copy;
            can_print = other.can_print;
            size = other.size;
            const std::type_info *current = other.info;
        }
        return *this;
    }

    ~Extra()
    {
        // WHAT TO DO HERE?
        // cout << "SHOULD DELETE DATA OF TYPE: " << (*this->info).name() << endl;
    }

    const std::type_info &type()
    {
        return *this->info;
    }

    template <typename T>
    T &as()
    {
        return *(T *)(value);
    }

    template <typename T>
    bool is()
    {
        return typeid(T) == *info;
    }

    friend std::ostream &operator<<(std::ostream &os, Extra obj)
    {
        if (typeid(int) == *obj.info)
        {
            os << *(int *)obj.value;
        }
        else if (typeid(float) == *obj.info)
        {
            os << *(float *)obj.value;
        }
        else if (typeid(char *) == *obj.info)
        {
            os << *(char **)obj.value;
        }
        else if (typeid(const char *) == *obj.info)
        {
            os << *(char **)obj.value;
        }
        else if (obj.can_print)
        {
            corem::printable *p = static_cast<corem::printable *>(obj.value);
            char *value = p->toString();
            os << value;
            delete[] value;
        }
        else
        {
            os << obj.value;
        }
        return os;
    }
};