#ifndef STATICARRAY_H
#define STATICARRAY_H

#include "array.h"

namespace ZWJ {
template<typename T, int N>
class StaticArray : public Array<T>
{
protected:
    T _staticArray[N];
public:
    StaticArray()
    {
        _array = _staticArray;
    }

    StaticArray(const StaticArray<T, N> &array)
    {
        _array = _staticArray;
        for(int i = 0; i< N; ++i)
            _array[i] = array[i];
    }

    StaticArray<T, N>& operator = (const StaticArray<T, N> &array)
    {
        if (this != &array)
            for(int i = 0; i< N; ++i)
                _array[i] = array[i];
        return *this;
    }

    int length() const
    {
        return N;
    }


};
}


#endif // STATICARRAY_H
