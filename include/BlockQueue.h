#ifndef THREADCPP_BLOCKQUEUE_H_
#define THREADCPP_BLOCKQUEUE_H_
#include <pthread.h>

#include <queue>
#include <utility>

#include "Condition.h"
#include "MutexLock.h"
#include "MutexLockGuard.h"

namespace EventLoop
{
    template<typename T>
    class BlockQueue
    {
    public:
        BlockQueue(unsigned int size = 1024);

        void put(const T &data);

        T get();

        ~BlockQueue();

        int size();

    private:
        MutexLock producerLock_;
        Condition producercond_;
        MutexLock consumerLock_;
        Condition consumercond_;
        std::queue<T> q_;
        unsigned int maxSize_;
    };

} /* namespace EventLoop */


namespace EventLoop
{
    template<typename T>
    BlockQueue<T>::BlockQueue(unsigned int size):
        producercond_(producerLock_),
        consumercond_(consumerLock_),
        maxSize_(size)
    {
    }

    template<typename T>
    void BlockQueue<T>::put(const T &data)
    {
        if (q_.size() >= maxSize_)
        {
            MutexLockGuard guard(consumerLock_);
            consumercond_.wait();
        }

        MutexLockGuard guard(producerLock_);
        q_.push(data);
        producercond_.notify();
    }

    template<typename T>
    T BlockQueue<T>::get()
    {
        if(q_.empty()) {
            MutexLockGuard guard(producerLock_);
            producercond_.wait();
        }

        MutexLockGuard guard(consumerLock_);
        T data(q_.front());
        q_.pop();
        consumercond_.notify();

        return data;
    }

    template<typename T>
    int BlockQueue<T>::size()
    {
        return q_.size();
    }

    template<typename T>
    BlockQueue<T>::~BlockQueue()
    {
    }

} /* namespace EventLoop */
#endif /* THREADCPP_BLOCKQUEUE_H_ */
