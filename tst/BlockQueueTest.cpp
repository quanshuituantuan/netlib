#include <stdio.h>

#include <gtest/gtest.h>
#include <utility>

#include "BlockQueue.h"
#include "MutexLock.h"

using namespace EventLoop;

class BlockQueueTest: public testing::Test
{
protected:
    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }

    MutexLock mutexlock_;
};

TEST_F(BlockQueueTest, create)
{
    BlockQueue<std::pair<int, int>> q;
}

TEST_F(BlockQueueTest, put_get)
{
    BlockQueue<std::pair<int, int>> q;
    q.put(std::make_pair(2, 2));
    EXPECT_EQ(std::make_pair(2, 2), q.get());
}

TEST_F(BlockQueueTest, doublePutGet)
{
    BlockQueue<double> q;
    double v = 1.1;
    q.put(v);
    EXPECT_EQ(v, q.get());
}

/**
 * this case will block testing
 */
//TEST_F(BlockQueueTest, blockWhenQueueIsFull)
//{
//    BlockQueue<int> q(2);
//    int v = 1;
//    q.put(v);
//    q.put(v);
//    q.put(v);
//}

/**
 * this case will block testing
 */
//TEST_F(BlockQueueTest, blockWhenQueueIsEmpty)
//{
//    BlockQueue<int> q(5);
//    int v = 1;
//    q.put(v);
//    q.put(v);
//    q.get();
//    q.get();
//    q.get();
//}
