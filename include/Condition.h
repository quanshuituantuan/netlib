#ifndef THREADCPP_CONDITION_H_
#define THREADCPP_CONDITION_H_

#include <pthread.h>
#include <stdint.h>

#include "MutexLock.h"

namespace EventLoop
{
    class Condition
    {
    public:
        Condition(MutexLock &mutexlock);

        Condition(const Condition &) = delete;

        Condition & operator = (const Condition &) = delete;

        void notify();

        void notifyAll();

        void wait();

        void waitTimeout(uint32_t second);

        ~Condition();

    private:
        MutexLock &mutexlock_;
        pthread_cond_t cond_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_CONDITION_H_ */
