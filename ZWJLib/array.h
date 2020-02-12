#ifndef ARRAY_H
#define ARRAY_H

#include "Object.h"
#include "Exception.h"
namespace ZWJ {

template <typename T>
class Array : public Object
{
protected:
    T* _array;
public:
    virtual bool get(int i, T &t)
    {
        bool ref = (0 <= i && i <length());
        if (ref)
            t = _array[i];
  // no need throw Exception
//        else
//            THROW_EXCEPTION(IndexOutOfBoundsException, "index out of Array bounds");
        return ref;
    }

    virtual bool set(int i, const T&t)
    {
        bool ref = (0 <= i && i <length());
        if (ref)
            _array[i] = t;
        // no need throw Exception
      //        else
      //            THROW_EXCEPTION(IndexOutOfBoundsException, "index out of Array bounds");
        return ref;
    }

    virtual int length() const = 0;

     T& operator[](int i)
     {
         bool ref = (0 <= i && i < length());
         if (ref)
             return _array[i];
         else
             THROW_EXCEPTION(IndexOutOfBoundsException, "index out of Array bounds");
     }

     T operator[](int i) const
     {
         return (const_cast<Array<T>&>(*this))[i];
     }
};
}
#endif // ARRAY_H
