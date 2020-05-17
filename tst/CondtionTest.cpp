#include <stdio.h>
#include <limits.h>
#include <time.h>

#include <gtest/gtest.h>
#include <iostream>

#include "Condition.h"
#include "ErrorCheck.h"

using namespace EventLoop;

class QuickTest: public testing::Test
{
protected:
    virtual void SetUp()
    {
        start_ = time(NULL);
    }

    virtual void TearDown()
    {
        end_ = time(NULL);
        time_t duration = end_ - start_;
        EXPECT_LE(duration, 2);
    }
    time_t start_;
    time_t end_;
};

class ConditionTest: public QuickTest
{
};

TEST_F(ConditionTest, create)
{
    MutexLock mutexlock;
    Condition cond(mutexlock);
}

//TEST_F(ConditionTest, timedwait)
//{
//    MutexLock mutexlock;
//    Condition cond(mutexlock);
//    EXPECT_THROW(cond.waitTimeout(1), ReturnErrorException);
//}

