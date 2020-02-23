#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "LinuxList.h"
#include "DualLinkList.h"

namespace ZWJ
{


template <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };

    list_head _header;
    list_head*  _current;

    list_head* position(int i) const
    {
        list_head *ret = const_cast<list_head *>(&_header);
        for( int p = 0; p < i; p++)
            ret = ret->next;
        return ret;
    }

    int mod (int i) const
    {
        return (_length == 0) ? 0 : i % _length;
    }

public:

    DualCircleList()
    {
        _length = 0;
        _step = 1;
        _current = NULL;
        INIT_LIST_HEAD(&_header);
    }

    bool insert(int i, const T &e)
    {
        bool ret = true;
        Node* node = new Node();
        i = i % (_length + 1);
        if (node != NULL) {
            node->value = e;
            list_add_tail(&node->head, position(i)->next);
            _length++;
        } else
            THROW_EXCEPTION(NoEnoughMemoryException, "No enough memory for DualCircleList");
        return ret;
    }

    bool remove(int i)
    {
       bool ret = true;
       i = mod(i);
       ret = (0 <=i) && (i <_length);
       if (ret) {
           list_head *toDel = position(i)->next;
           if (_current == toDel)
               _current = toDel->next;
           list_del(toDel);
           _length--;
           delete list_entry(toDel, Node, head);

       }
       return ret;
    }

    bool set(int i, const T &e)
    {
        bool ref = true;
        i = mod(i);
        ref = ((0 <= i) && (i < _length));
        if (ref)
            list_entry(position(i)->next, Node, head)->value = e;
        return ref;
    }

    bool get(int i, T&e) const
    {
        bool ref = true;
        i = mod(i);
        ref = ((0 <= i) && (i < _length));
        if (ref)
            e = list_entry(position(i)->next, Node, head)->value;
        return ref;
    }
    T get(int i) const
    {
         T e;
        bool ref =get(i, e);
        if (ref)
            return e;
        else
            THROW_EXCEPTION(IndexOutOfBoundsException, "index out of Bounds in LinkList");
    }

    int find (const T &e) const
    {
        int ref = -1;
        int i = 0;
        list_head *slider = NULL;
        list_for_each(slider, &_header) {
            if (list_entry(slider, Node, head)->value == e) {
                ref = i;
                break;
            }
            ++i;
        }
        return ref;
    }

    int length() const
    {
        return _length;
    }

    void clear()
    {
        while(_length > 0)
            remove(0);
    }

    bool move(int i, int step = 1)
    {
        bool ret = (step > 0);
        i = mod(i);
        ret = ret && (0 <= i) && (i <_length);
        if (ret) {
            _current = position(i)->next;
            _step = step;
        }
        return ret;
    }

    bool end()
    {
        return (_current == NULL) || (_length == 0);
    }

    T current()
    {
        if(!end())
            return list_entry(_current, Node, head)->value;
        else
            THROW_EXCEPTION(InvalidOperationException, "no value at current position ...");

    }

    bool next()
    {
        int i = 0;
        while ((i < _step) && !end()) {
            if (_current != &_header) {
                _current = _current->next;
                i++;
            }else
                _current = _current->next;
        }
        if (_current == &_header)
            _current = _current->next;
        return ( i == _step);
    }

    bool pre()
    {
        int i = 0;
        while ((i < _step) && !end()) {
            if (_current != &_header) {
                _current = _current->prev;
                i++;
            }else
                _current = _current->prev;
        }
        if (_current == &_header)
            _current = _current->prev;
        return ( i == _step);
    }

    ~DualCircleList()
    {
        clear();
    }
};
}

#endif // DUALCIRCLELIST_H
