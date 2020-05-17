#include <stdio.h>

#include "ErrorCheck.h"
#include "MutexLock.h"

namespace EventLoop
{

    MutexLock::MutexLock()
    {
        TCHECK(pthread_mutex_init(&mutex_, NULL));
    }

    pthread_mutex_t & MutexLock::getMutex()
    {
        return mutex_;
    }

    void MutexLock::lock()
    {
        TCHECK(pthread_mutex_lock(&mutex_));
    }

    void MutexLock::unlock()
    {
        TCHECK(pthread_mutex_unlock(&mutex_));
    }

    MutexLock::~MutexLock()
    {
        pthread_mutex_destroy(&mutex_);
    }

} /* namespace EventLoop */
