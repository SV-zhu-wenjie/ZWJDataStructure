#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include "Pointer.h"
#include "Exception.h"

namespace ZWJ {

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int *_ref;
    void init(const SharedPointer<T> &obj)
    {
        _pointer = obj._pointer;
        _ref = obj._ref;
        if (_ref != NULL)
            *_ref = *_ref + 1;
    }

public:
#ifdef Z
explicit SharedPointer(T *p = nullptr) : Pointer<T>(p)
    {
        if (p == NULL)
            _ref = NULL;
        _ref = new int;
        *_ref = 1;
    }
#endif

explicit SharedPointer(T *p = NULL): _ref(NULL)
    {
        if (p) {
            _ref = static_cast<int *>(std::malloc(sizeof(int)));
            if (_ref) {
                *_ref = 1;
                _pointer = p;
            }
            else
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPoint object");


        }
    }

    SharedPointer(const SharedPointer<T> &obj)
    {
        init(obj);
    }

    SharedPointer<T>& operator= (const SharedPointer<T> &obj)
    {
        if (this != &obj) {
            clear();
            init(obj);
        }
        return *this;
    }
#ifdef Z
    void clear()// bug
    {
        if (_ref == NULL)
            return;
        *_ref = *_ref - 1;
        if (*_ref == 0) {
            delete _pointer;
            delete _ref;
            _pointer = NULL;
            _ref = NULL;
        }

    }
#endif

    void clear()
    {
        T *toDel = _pointer;
        int *ref = _ref;
        _pointer = NULL;
        _ref = NULL;
        if (ref) {
            (*ref)--;
            if (*ref == 0) {
                free (ref);
                delete toDel;
            }
        }

    }

    ~SharedPointer()
    {
        clear();
    }

};

template<typename T>
bool operator == (const SharedPointer<T>& l, const SharedPointer<T> &r)
{
    return (l.get() == r.get());
}

template<typename T>
bool operator != (const SharedPointer<T>& l, const SharedPointer<T> &r)
{
    return !(l == r);
}

}

#endif // SHAREDPOINTER_H
