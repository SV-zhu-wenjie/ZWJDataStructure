#ifndef LINKLIST_H
#define LINKLIST_H

#include "List.h"
#include "Exception.h"
namespace ZWJ {

template <typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T vale;
        Node *next = NULL;
    };
    mutable struct : public Object{
       char reserved[sizeof(T)];
       Node *next = NULL;
    } _header;
    int  _length;

    Node * position(int i) const
    {
        Node *curNode = reinterpret_cast<Node*>(&_header);
        for (int p = 0; p < i; ++p)
            curNode = curNode->next;
        return curNode;
    }

public:
    LinkList()
    {
        _header.next = NULL;
        _length = 0;
    }
    bool insert(int i, const T &e)
    {
#ifdef Z
        bool ref = ((i <=0) && (i < _length));
        if (ref) {
            Node *curNode = _header;
            for (int j = 0; j < i; ++j)
                curNode = curNode->next;
            Node *nextNode = curNode->next;
            Node *insertNode = new Node;
            if (insertNode != NULL) {
                insertNode->vale = e;
                curNode->next = newNode;
                newNode->next = nextNode;
                ++_length;
            }
            else
                THROW_EXCEPTION(NoEnoughMemoryException, "no enough memory for LinkList");
        }
#endif
        bool ref = ((0 <= i) && (i <= _length));
        if (ref) {
            Node *node = new Node;
            if (node != NULL) {
                Node *curNode = position(i);
                node->vale = e;
                node->next = curNode->next;
                curNode->next = node;
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
            curNode->next = node->next;
            delete node;
            --_length;
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

    bool get(int i, T&e)
    {
        bool ref = ((0 <= i) && (i < _length));
        if (ref) {
            Node *curNode = position(i);
            e = curNode->next->vale;
        }
        return ref;
    }
    T get(int i) {
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
#ifdef Z
        Node *curNode = _header;
        for (int i = 0; i < _length; ++i) {
            Node * node = curNode;
            curNode = curNode->next;
            delete node;
        }
#endif
        while (_header.next) {
            Node *toDel = _header.next;
            _header.next = toDel->next;
            delete toDel;
        }
        _length = 0;

    }
    ~LinkList()
    {
        clear();
    }

};
}


#endif // LINKLIST_H
