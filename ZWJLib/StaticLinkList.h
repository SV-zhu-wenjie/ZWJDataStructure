#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H
#include "LinkList.h"
#include "StaticList.h"
#include <cstddef>

namespace ZWJ {

template<typename T, int N>
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node;
    struct SNode : public Node
    {
        void *operator new(size_t, void *loc)
        {
            return loc;
        }
    };

    unsigned char _space[sizeof(Node) * N];
  //  StaticList<int, N> spaceList;

    bool _used[N];
    Node *create()
    {
/*        if (spaceList.length() == 0)
            return NULL;
        int n = spaceList[spaceList.length() - 1];
        Node *node = reinterpret_cast<Node*>(_space[n * sizeof(Node)]);
        node->Node();
        return node; */

        SNode *ret = NULL;
        for (int i = 0; i < N; ++i)
            if (!_used[i]) {
                ret = reinterpret_cast<SNode*>(_space) + i;
                ret = new(ret)SNode();
                _used[i] = true;
                break;
            }
        return ret;
    }
    void destory(Node *p)
    {
        SNode *space = reinterpret_cast<SNode*>(_space);
        SNode *psn = dynamic_cast<SNode*>(p);
        for (int i = 0; i < N; ++i) {
            if(psn == (space + i)) {
                _used[i]= false;
                psn->~SNode();
            }

        }

    }

public:
    StaticLinkList() : LinkList<T>()
    {
//        for (int i = 0; i< N; ++i)
//            spaceList.insrt(0, i);
        for (int i = 0; i < N; ++i)
            _used[i] = false;

    }
    int capacity()
    {
        return N;
    }
    ~StaticLinkList()
    {
       clear();
    }
};
}
#endif // STATICLINKLIST_H
