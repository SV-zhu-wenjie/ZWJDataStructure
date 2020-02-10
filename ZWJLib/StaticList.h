#ifndef STATICLIST_H
#define STATICLIST_H
#include "Seqlist.h"

namespace ZWJ {

template <typename T, int N>
class StaticList : public SeqList<T>
{
protected:
    T _t[N];
public:
    StaticList()
    {
        _array = _t;
        _length = 0;
    }
    int capacity() const
    {
        return N;
    }
};
}




#endif // STATICLIST_H
