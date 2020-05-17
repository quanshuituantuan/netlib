#include <stdio.h>

#include "Condition.h"
#include "ErrorCheck.h"

namespace EventLoop
{

    Condition::Condition(MutexLock &mutexlock): mutexlock_(mutexlock)
    {
        TCHECK(pthread_cond_init(&cond_, NULL));
    }

    void Condition::notify()
    {
        TCHECK(pthread_cond_signal(&cond_));
    }

    void Condition::notifyAll()
    {
        TCHECK(pthread_cond_broadcast(&cond_));
    }

    void Condition::wait()
    {
        TCHECK(pthread_cond_wait(&cond_, &mutexlock_.getMutex()));
    }

    void Condition::waitTimeout(uint32_t second)
    {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);

        abstime.tv_sec += second;
        abstime.tv_nsec += 0;

        TCHECK(pthread_cond_timedwait(&cond_, &mutexlock_.getMutex(), &abstime));
    }

    Condition::~Condition()
    {
        pthread_cond_destroy(&cond_);
    }

} /* namespace EventLoop */
