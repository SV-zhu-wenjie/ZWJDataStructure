#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"
namespace ZWJ {

template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T vale;
        Node *next = NULL;
        Node *pre = NULL;
    };
    mutable struct : public Object{
       char reserved[sizeof(T)];
       Node *next = NULL;
       Node *pre;
    } _header;
    int  _length;
    Node *_curNode;
    int _step;
    Node * position(int i) const // O(n)
    {
        Node *curNode = reinterpret_cast<Node*>(&_header);
        for (int p = 0; p < i; ++p)
            curNode = curNode->next;
        return curNode;
    }


    virtual Node *create()
    {
        return new Node();
    }

    virtual void destory(Node *p)
    {
        delete p;
    }

public:
    DualLinkList()
    {
        _header.next = NULL;
        _header.pre = NULL;

        _length = 0;
        _curNode = NULL;
        _step = 1;
    }
    bool insert(int i, const T &e)
    {
        bool ref = ((0 <= i) && (i <= _length));
        if (ref) {
            Node *node = create();
            if (node != NULL) {
                Node *curNode = position(i);
                Node *next = curNode->next;
                node->vale = e;
                node->next = next;
                curNode->next = node;
                if (curNode != reinterpret_cast<Node*>(&_header))
                    node->pre = curNode;
                else
                    node->pre = NULL;
                if(next != NULL)
                    next->pre = node;
                ++_length;
            }else
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory for LinkList");
        }
        return ref;

    }

    bool remove(int i)
    {
        bool ref = ((0 <= i) && (i < _length));
        if (ref) {
            Node *curNode = position(i);
            Node *node = curNode->next;
            Node *next = node->next;

            curNode->next = next;
            if (_curNode == node)
                _curNode = next;
            if (next != NULL)
                next->pre = curNode->pre;
            // exception safe
            --_length;
            destory(node);
        }
        return ref;
    }

    bool set(int i, const T &e)
    {
        bool ref = ((0 <= i) && (i < _length));
        if (ref) {
            Node *curNode = position(i);
            curNode->next->vale = e;
        }
        return ref;


    }

    bool get(int i, T&e) const
    {
        bool ref = ((0 <= i) && (i < _length));
        if (ref) {
            Node *curNode = position(i);
            e = curNode->next->vale;
        }
        return ref;
    }
    T get(int i) const
    {
        bool ref = ((0 <= i) && (i < _length));
        if (ref) {
            Node *curNode = position(i);
            return  curNode->next->vale;
        } else
            THROW_EXCEPTION(IndexOutOfBoundsException, "index out of Bounds in LinkList");
    }

    int length() const
    {
        return _length;
    }
    void clear()
    {
        while (_length > 0)
            remove(0);
    }

    int find (const T &e)
    {
        int ret = -1;
        int i = 0;
        Node *node = _header.next;
        while(node != NULL) {
            if (node->vale == e) {
                ret = i;
                break;
            }
            node = node->next;
            ++i;
        }
        return ret;
    }

    virtual bool move(int i, int step = 1)
    {
        bool ref = (0 <= i) && (i < _length) && (step > 0);
        if (ref) {
            _curNode = position(i)->next;
            _step = step;
        }
        return ref;
    }
    virtual bool end()
    {
        return (_curNode == NULL);

    }

    virtual T current()
    {
        if (!end())
            return _curNode->vale;
        else
            THROW_EXCEPTION(InvalidOperationException, "No value at current position");
    }
    virtual bool next()
    {
        bool ref  = true;;
        for (int i = 0; i < _step; ++i)
            if (!end() && _curNode != NULL)
                _curNode = _curNode->next;
            else {
                ref = false;
                break;
            }
        return ref;
    }

    virtual bool pre()
    {
        bool ref  = true;;
        for (int i = 0; i < _step; ++i)
            if (!end() && _curNode != NULL)
                _curNode = _curNode->pre;
            else {
                ref = false;
                break;
            }
        return ref;
    }

    ~DualLinkList()
    {
        clear();
    }

};
}

#endif // DUALLINKLIST_H
