#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Pointer.h"

namespace ZWJ
{
template <typename T>
class SmartPoint : public Pointer<T>
{
public:
    explicit SmartPoint(T* p = nullptr): Pointer<T>(p)
    {
    }

    SmartPoint(const SmartPoint<T> &obj)
    {
        _pointer = obj._pointer;
        const_cast<SmartPoint<T>&>(obj)._pointer = nullptr;
    }
    SmartPoint<T>& operator= (const SmartPoint<T> &obj)
    {
        if (this != &obj) {
            T *p = _pointer;
            _pointer = obj._pointer;
            const_cast<SmartPoint<T>&>(obj)._pointer = nullptr;
            delete p;
        }
        return *this;
    }

    ~SmartPoint()
    {
        delete _pointer;
    }
};
}


#endif // SMARTPOINTER_H
