#include <gtest/gtest.h>

#include "CallBackQueue.h"

using namespace EventLoop;
using namespace testing;

class CallBackQueueTest: public Test
{
};

class Sum
{
public:
    Sum():sum_(0)
    {
    }

    void add(int v)
    {
        sum_ += v;
    }

    int sum_;
};

TEST_F(CallBackQueueTest, create)
{
    CallBackQueue q;
}

TEST_F(CallBackQueueTest, count)
{
    CallBackQueue q;

    q.schedule([](){});
    q.schedule([](){});

    EXPECT_EQ(2, q.count());
}

TEST_F(CallBackQueueTest, run)
{
    CallBackQueue q;
    Sum sum;

    q.schedule(std::bind(&Sum::add, &sum, 3));
    q.run();
    EXPECT_EQ(3, sum.sum_);

    q.schedule(std::bind(&Sum::add, &sum, 8));
    q.run();
    EXPECT_EQ(11, sum.sum_);

}




