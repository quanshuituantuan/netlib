#ifndef THREADCPP_MUTEXLOCKGUARD_H_
#define THREADCPP_MUTEXLOCKGUARD_H_
#include "MutexLock.h"
#include "NoneCopyable.h"

namespace EventLoop
{
    class MutexLockGuard: public NoneCopyable
    {
    public:
        MutexLockGuard(MutexLock &mutexlock);

        ~MutexLockGuard();

    private:
        MutexLock &mutexlock_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_MUTEXLOCKGUARD_H_ */
