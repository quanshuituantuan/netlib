#include <stdio.h>
#include <pthread.h>

#include <gtest/gtest.h>

#include "MutexLock.h"

using namespace EventLoop;

TEST(MutexLock, create)
{
    MutexLock mutexlock;
}

TEST(MutexLock, getMutex)
{
    MutexLock mutexlock;
    pthread_mutex_t mutex = mutexlock.getMutex();
    mutex = mutex;
}



