#ifndef THREADCPP_MUTEXLOCK_H_
#define THREADCPP_MUTEXLOCK_H_
#include <pthread.h>

#include "NoneCopyable.h"

namespace EventLoop
{

    class MutexLock: public NoneCopyable
    {
    public:
        MutexLock();

        pthread_mutex_t & getMutex();

        void lock();

        void unlock();

        ~MutexLock();

    private:
        pthread_mutex_t mutex_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_MUTEXLOCK_H_ */
