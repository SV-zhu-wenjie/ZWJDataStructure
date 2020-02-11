#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include "Seqlist.h"
#include "Exception.h"

namespace ZWJ {


template <typename T>
class DynamicList : public SeqList<T>
{
protected:
    int _capcity;
public:
    DynamicList(int capcity)
    {
        _array = new T[capcity];
        if (_array) {
            _capcity = capcity;
            _length = 0;
        } else
            THROW_EXCEPTION(NoEnoughMemoryException, "no enough memeory");
    }
    int capacity() const
    {
        return _capcity;
    }
    void resize(int capcity)
    {
#ifdef  A
        T *temp = _array;
        _array = new T[capcity];
        if (_array) {
            _length = _length < capcity ? _length : capcity;
            for (int i = 0; i< _length; ++i)
                _array[i] = temp[i];
            _capcity = capcity;
        }
        delete []temp;
#endif
        if (capcity == capacity())
            return;
        T *temp = new T[capcity];
        if (temp != NULL) {
            _length = _length = _length < capcity ? _length : capcity;
            for (int i = 0; i< _length; ++i)
                temp[i] = _array[i];
            _capcity = capcity;
            delete[]  _array;
            _array = temp;
        } else
            THROW_EXCEPTION(NoEnoughMemoryException, "no enough memeory");
    }

    ~DynamicList()
    {
        delete[] _array;

    }
};

}



#endif // DYNAMICLIST_H
