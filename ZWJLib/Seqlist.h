#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"
namespace ZWJ {

template <typename T>
class SeqList : public List<T>
{
protected:
    T* _array;
    int _length;
public:
    bool insert(int i, const T &e)
    {
        bool ret = ( 0 <= i &&  i <=_length);
        ret = ret && (_length < capacity());
        if (ret) {
            for (int p = _length -1; p >= i; p--)
                _array[p + 1] = _array[p];
            _array[i] = e;
            _length++;
        }
        return ret;
    }
    bool remove(int i)
    {
        bool ret = ( 0 <= i &&  i <_length);
        if (ret) {
            for (int p  = i; p < _length - 1; p ++)
                _array[p] = _array[p + 1];
            _length --;
        }
        return ret;
    }
    bool set(int i, const T &e)
    {
        bool ret = ( 0 <= i &&  i <_length);
        if (ret)
            _array[i] = e;
        return ret;
    }

    bool get(int i, T&e)
    {
        bool ret = ( 0 <= i &&  i <_length);
        if (ret)
            e = _array[i];
        return ret;
    }

    int length() const
    {
        return _length;
    }
    void clear()
    {
        _length = 0;
    }

    int find(const T &e)
    {
        int ret = -1;
        for (int i = 0; i < _length; ++i)
            if (_array[i] == e)
                return i;
        return ret;

    }
    // 数组访问方式
    T& operator [](int i)
    {
        if (0 <= i && i < _length)
            return _array[i];
        else
            THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }

    T  operator [](int i) const
    {
      //  return  (const_cast<SelList<T>*>(this))->operator [](i);
        return (const_cast<SeqList<T>&>(*this))[i];

    }


    virtual int capacity() const = 0;
};


}




#endif // SEQLIST_H
