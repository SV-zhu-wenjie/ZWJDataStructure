#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "array.h"

namespace ZWJ {
template<typename T>
class DynamicArray : public Array<T>
{
protected:
    int _length ;
 //     T *copy (const T*t, int n)
    T *copy (const T*t, int len, int newLen)// O(min(len, newlen)
    {
        T *temp = new T[newLen];
        if (temp != nullptr) {
            int n = len < newLen ? len : newLen;
            for (int i = 0; i < n; ++i)
                temp[i] = t[i];
        }
        return temp;
    }

    void update (T* t, int n)
    {
        if ( t != nullptr) {
            auto temp = _array;
            _array = t;
            _length = n;
            if (temp != NULL)
                delete temp;
        } else
            THROW_EXCEPTION(NoEnoughMemoryException, "DynamicArray: no enough memory");
    }

    void init(T *t, int n)
    {
        if (t!= nullptr) {
            _array = t;
            _length = n;
        }else
            THROW_EXCEPTION(NoEnoughMemoryException, "DynamicArray: no enough memory");

    }
public:
    DynamicArray(int n = 0)
    {
        if (n == 0) {
            _length = 0;
            _array = NULL;
            return;
        }
        init (new T[n], n);
    }

    DynamicArray(const DynamicArray<T> &array)
    {
#ifdef Z
        _array = new T[array.length()];
        if(_array != nullptr) {
            _length = array.length();
            for (int i = 0; i < _length; ++i)
                _array[i] = array._array[i];
        } else
            THROW_EXCEPTION(NoEnoughMemoryException, "DynamicArray: no enough memory");
#endif

        init (copy(array._array, array._length, array._length), array._length);
    }

    DynamicArray<T>& operator = (const DynamicArray<T> &array)
    {
        update(copy(array._array, _length, array.length()), array.length());
        return *this;
    }

    int length() const
    {
        return _length;
    }

    void resize(int length)
    {
        if (length == _length)
            return;
        update(copy(_array, _length, length), length);
    }
    //
    ~DynamicArray()
    {
        delete[] _array;
    }
};
}
#endif // DYNAMICARRAY_H
