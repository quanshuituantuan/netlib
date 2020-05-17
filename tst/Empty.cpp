#include <stdio.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Epoll.h"

using namespace EventLoop;
using namespace testing;

class EmptyTest: public Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(EmptyTest, create)
{
	 EXPECT_EQ(2, 2);
}



