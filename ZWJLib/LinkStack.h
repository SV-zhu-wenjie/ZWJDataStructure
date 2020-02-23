#ifndef LINKSTACK_H
#define LINKSTACK_H

#include "Stack.h"
#include "Exception.h"
#include "LinkList.h"

namespace ZWJ {

template <typename T>
class LinkStack : public Stack<T>
{
protected:
    LinkList<T> _linkList;

public:
    LinkStack() {}

    void push(const T &e)
    {
        _linkList.insert(0, e);
    }

    void pop()
    {
        if (_linkList.length() > 0)
            _linkList.remove(0);
        else
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack");
    }

    T top()
    {
        if (_linkList.length() > 0)
            return _linkList.get(0);
        else
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack");
    }

    int size() const
    {
        return _linkList.length();
    }

    void clear()
    {
        _linkList.clear();
    }

};

}
#endif // LINKSTACK_H
