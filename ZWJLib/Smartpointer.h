#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "Object.h"

namespace ZWJ
{
template <typename T>
class SmartPoint : public Object
{
 protected:
    T* smartPoint;
public:
    explicit SmartPoint(T* p = nullptr)
    {
        smartPoint = p;
    }

    SmartPoint(const SmartPoint<T> &obj)
    {
        smartPoint = obj.smartPoint;
        const_cast<SmartPoint<T>&>(obj).smartPoint = nullptr;
    }

    SmartPoint<T>& operator= (const SmartPoint<T> &obj)
    {
        if (this != &obj) {
            delete smartPoint;
            smartPoint = obj.smartPoint;
            const_cast<SmartPoint<T>&>(obj).smartPoint = nullptr;
        }
        return *this;
    }

    T* operator->()
    {
        return smartPoint;
    }

    T& operator* ()
    {
        return *smartPoint;
    }

    bool isNull () const
    {
        return smartPoint == nullptr;
    }

    T* get()
    {
        return smartPoint;
    }

    ~SmartPoint()
    {
        delete smartPoint;
    }
};
}


#endif // SMARTPOINTER_H
