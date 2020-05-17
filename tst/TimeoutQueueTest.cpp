#include <gtest/gtest.h>
#include <iostream>

#include "TimeoutQueue.h"

using namespace EventLoop;
using namespace testing;

class TimeoutQueueTest: public Test
{

};

void inc(int &value)
{
    value++;
}

TEST_F(TimeoutQueueTest, create)
{
    TimeoutQueue q;
}

TEST_F(TimeoutQueueTest, count)
{
    TimeoutQueue q;
    q.schedule(0, [](){});
    q.schedule(3, [](){});

    EXPECT_EQ(2, q.count());
}

TEST_F(TimeoutQueueTest, run)
{
    TimeoutQueue q;
    int sum(0);

    q.schedule(0, std::bind(inc, std::ref(sum)));
    q.schedule(1, std::bind(inc, std::ref(sum)));
    q.schedule(2, std::bind(inc, std::ref(sum)));

    q.run();
    EXPECT_EQ(1, sum);
}

TEST_F(TimeoutQueueTest, runAndElapse)
{
    TimeoutQueue q;
    int sum(0);

    q.schedule(0, std::bind(inc, std::ref(sum)));
    q.schedule(2, std::bind(inc, std::ref(sum)));
    q.schedule(2, std::bind(inc, std::ref(sum)));
    q.schedule(3, std::bind(inc, std::ref(sum)));
    q.run();

    q.elapse(1);
    q.run();
    EXPECT_EQ(1, sum);

    q.elapse(1);
    q.run();
    EXPECT_EQ(3, sum);

    q.elapse(1);
    q.run();
    EXPECT_EQ(4, sum);
}

TEST_F(TimeoutQueueTest, overElapse)
{
    TimeoutQueue q;
    int sum(0);

    q.schedule(2, std::bind(inc, std::ref(sum)));
    q.schedule(2, std::bind(inc, std::ref(sum)));
    q.schedule(2, std::bind(inc, std::ref(sum)));

    q.elapse(4);
    q.run();
    EXPECT_EQ(3, sum);
}

TEST_F(TimeoutQueueTest, overRun)
{
    TimeoutQueue q;
    int sum(0);

    q.schedule(0, std::bind(inc, std::ref(sum)));
    q.schedule(0, std::bind(inc, std::ref(sum)));
    q.schedule(0, std::bind(inc, std::ref(sum)));

    q.run();
    q.run();
    EXPECT_EQ(3, sum);
}



