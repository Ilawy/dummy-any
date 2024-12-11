#include "iostream"

using namespace std;

enum FlexStackError
{
    StackIsFull,
    StackIsEmpty
};

/*
    init
        size = grower
        items = T[grower]

    grow
        size += grower
        (realloc)

    shrink
        size -= grower
        (realloc)

    push
        if top >= size (FULL)
            grow()
        items[top] = item
        top++

    pop
        if top <= size
            ERROR stack is empty
        else
            top--
            cuurent = items[top]
            if(top % grower == 0)
                shrink()
            return current

*/

template <typename T>
class FlexStack
{
private:
    int size = 0;
    int top = 0;
    int grower;
    T *items;
    void grow()
    {
        int old_size = this->size;
        this->size += this->grower;
        // cout << "GROW :: " << this->size << endl;
        T *new_ptr = new T[this->size];

        for (int i = 0; i < old_size; i++)
        {
            new_ptr[i] = this->items[i];
        }
        // cout << "GROW :: " << this->size << endl;
        delete[] this->items;
        this->items = new_ptr;
    }

    void shrink()
    {
        // cout << "this->size(" << this->size << ")" << "this->grower(" << this->grower << ")" " = " << this->size - this->grower;
        int old_size = this->size;
        this->size -= this->grower;
        T *new_ptr = new T[this->size];
        for (int i = 0; i < old_size; i++)
        {
            new_ptr[i] = this->items[i];
        }
        delete[] this->items;
        this->items = new_ptr;
    }

public:
    FlexStack(int grower = 8)
    {
        this->grower = grower;
        this->size = grower;
        this->top = 0;
        this->items = new T[this->size];
    }
    FlexStack(FlexStack &original)
    {
        this->size = original.size;
        this->top = original.top;
        this->items = new T[original.size];
        for (int i = 0; i < original.top; i++)
        {
            this->items[i] = original.items[i];
        }
    }
    ~FlexStack()
    {
        delete[] this->items;
    }

    // methods
    void push(T &item)
    {
        if (this->top >= this->size)
        { // FULL
            this->grow();
        }
        this->items[top++] = item;
        // cout << "PUSHED (" << item << ") AT (" <<  top-1 << ")\n";
    }
    // T &pop()
    // {
    //     if (this->top <= 0)
    //         throw FlexStackError::StackIsEmpty;
    //     cout << "TOP" << top << endl;
    //     return this->items[--top];
    //     // if (top % grower == 0 && this->size - this->grower > 0)
    //     // {
    //     //     this->shrink();
    //     // }
    //     // return value;
    // }
    T &pop()
    {
        if (this->top <= 0)
            throw FlexStackError::StackIsEmpty;

        T &value = this->items[--top];

        // if (top % grower == 0 && this->size - this->grower > 0)
        // {
        //     this->shrink();
        // }

        return value;
    }

    int getSize()
    {
        return this->top;
    }

    T *getItems()
    {
        return this->items;
    }

    T &operator[](int idx)
    {
        return this->items[idx];
    }
};