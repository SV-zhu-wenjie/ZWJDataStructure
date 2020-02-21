#ifndef POINTER_H
#define POINTER_H

#include <Object.h>
#include "iostream"

namespace ZWJ {

template<typename T>
class Pointer : public Object
{
protected:
    T* _pointer;
public:
    Pointer(T *p = NULL)
    {
        cout << "Pointer ctor" <<endl;
        _pointer = p;
        cout << _pointer <<endl;

    }
    T* operator->()
    {
        return _pointer;
    }

    T& operator*()
    {
        return *_pointer;

    }

    const T* operator->() const
    {
        return _pointer;
    }

    const T& operator*() const
    {
        return *_pointer;

    }

    bool isNull() const
    {
        return (_pointer == NULL);
    }

    T* get() const
    {
        return _pointer;
    }
};



}
#endif // POINTER_H
