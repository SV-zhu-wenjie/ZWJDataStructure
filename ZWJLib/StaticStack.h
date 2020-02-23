#ifndef STATICSTACK_H
#define STATICSTACK_H

#include "Stack.h"
#include "Exception.h"

namespace ZWJ
{

template <typename T, int N>
class StaticStack : public Stack<T>
{
protected:
    T _stack[N];
    int _top;
    int _size;
public:
    StaticStack()
    {
        _top = -1;
        _size = 0;
    }

    int capacity() const
    {
        return N;
    }

    void push(const T &e)
    {
        if (_size < N) {
            _stack[_top + 1] = e;
            _top++;
            _size++;
        } else
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack");

    }
    void pop()
    {
        if (_size >0) {
            _top--;
            _size--;
        }else
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack");
    }
     T top()
     {
         if (_size >0) {
             return _stack[_top];
         }else
             THROW_EXCEPTION(InvalidOperationException, "No element in current stack");
     }

     int size() const
     {
         return _size;
     }

     void clear()
     {
         _top = -1;
         _size = 0;
     }

};

}

#endif // STATICSTACK_H
