#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "LinkList.h"
#include "LinuxList.h"
#include "Exception.h"

namespace ZWJ {

template <typename T>
class LinkQueue : public Queue<T>
{
protected:
    struct Node: public Object
    {
        T value;
        list_head head;
    };

    list_head _header;
    int _length;

public:
    LinkQueue()
    {
        INIT_LIST_HEAD(_header);
        _length = 0;

    }

    void add(const T &e) //
    {
        Node *node = new Node();
        if (node != NULL) {
            node->value = e;
            list_add_tail(node->head, &_header);
            _length++;
        } else
            THROW_EXCEPTION(InvalidOperationException, "No ");
    }

    void remove() // O(1)
    {
        if (_length > 0) {
            list_head *toDel = _header.next;
            list_del(toDel);
            _length--;
            delete list_entry(toDel, Node, head);
        }else
        THROW_EXCEPTION(InvalidOperationException, "No element in current Queue!");
    }

    T front() const  // O(1)
    {
        if (_length > 0)
            return list_entry(_header.next, Node, head)->value;
       else
        THROW_EXCEPTION(InvalidOperationException, "No element in current Queue!");
    }

    void clear() // O(n)
    {
        while (_length > 0)
            remove();
    }

    int length() const // O(1)
    {
        return _length;
    }

    ~LinkQueue()
    {
        clear();
    }
};

}

#endif // LINKQUEUE_H
