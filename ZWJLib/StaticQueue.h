#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include "Queue.h"
#include "Exception.h"

namespace ZWJ
{

template <typename T, int N>
class StaticQueue : public Queue<T>
{
protected:
    T _space[N];
    int _front;
    int _rear;
    int _length;
public:
    StaticQueue()
    {
        _front = 0;
        _rear = 0;
        _length = 0;
    }

    int capacity() const
    {
        return N;
    }

    void add(const T &e)
    {
        if (_length < N) {
            _space[_rear] = e;
            _rear = (_rear + 1) % N;
            _length++;

        }else
            THROW_EXCEPTION(InvalidOperationException, "No space in current Queue!");
    }

    void remove()
    {
        if (_length > 0){
            _front = (_front + 1) % N;
            _length--;
        }else
            THROW_EXCEPTION(InvalidOperationException, "No element in current Queue!");
    }

    T front() const
    {
        if (_length > 0)
            return _space[_front];
        else
            THROW_EXCEPTION(InvalidOperationException, "No element in current Queue!");
    }

    void clear()
    {
        _front = 0;
        _rear = 0;
        _length = 0;
    }

    int length() const
    {
        return _length;
    }
};
}
#endif // STATICQUEUE_H
