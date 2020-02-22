#ifndef CIRCLELIST_H
#define CIRCLELIST_H

#include "LinkList.h"

namespace ZWJ {

template <typename T>
class CircleList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    Node* last() const
    {
        return position(length()- 1)->next;
    }

    void lastToFirst() const
    {
        last()->next = _header.next;

    }
    int mod(int i) const
    {
        return _length == 0 ? 0 : (i %_length);
    }

public:
    bool remove(int i)
    {
        bool ret = true;
        i = mod(i);
        if (i == 0) {
            Node *toDel = _header.next;
            if (toDel != NULL){
                _header.next = toDel->next;
                _length--;
                if (_length > 0) {
                    lastToFirst();
                    if (_curNode == toDel)
                        _curNode = toDel->next;

                }else {
                    _header.next = NULL;
                    _curNode = NULL;
                }
                destory(toDel);
            } else {
                ret = false;
            }
        } else
            ret = LinkList<T>::remove(i);
        return ret;
    }

    bool insert(int i, const T &e)
    {
        bool ret = true;
        i = i % (_length +  1);
        ret = LinkList<T>::insert(i, e);
        if (ret && i == 0)
            lastToFirst();
        return ret;
    }
    bool set(int i, const T &e)
    {
        return LinkList<T>::set(mod(i), e);
    }
    T get(int i) const
    {
        return LinkList<T>::get(mod(i));
    }
    bool get(int i, const T &e) const
    {
        return LinkList<T>::get(mod(i), e);
    }

    int find (const T&e) const
    {
        int ref = -1;
        for (int i = 0; i < _length; ++i)
            if (get(i) == e) {
                ref = i;
                break;
            }
        return ref;
    }

    void clear()
    {
        while(_length > 1)
            remove(1);
        if (_length == 1) {
            Node *toDel = _header.next;
            _header.next = NULL;
            _length = 0;
            _curNode = NULL;
            destory(toDel);
        }
    }

    bool move(int i, int step)
    {
        return LinkList<T>::move(mod(i), step);
    }

    bool end()
    {
        return (_length == 0) || (_curNode == NULL);
    }

    ~CircleList()
    {
        clear();
    }
};

void josephus(int n, int s, int m)
{
    CircleList<int> cl;
    for (int i = 0; i < n; ++i)
        cl.insert(i, i + 1);
    cl.move(s-1, m-1);
    while(cl.length() > 0) {
        cl.next();
        cout << cl.current() << endl;
        cl.remove(cl.find(cl.current()));
    }
}

}

#endif // CIRCLELIST_H
