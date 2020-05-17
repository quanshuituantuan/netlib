#include "MutexLockGuard.h"

namespace EventLoop
{

    MutexLockGuard::MutexLockGuard(MutexLock &mutexlock):mutexlock_(mutexlock)
    {
        mutexlock_.lock();
    }

    MutexLockGuard::~MutexLockGuard()
    {
        mutexlock_.unlock();
    }

} /* namespace EventLoop */
