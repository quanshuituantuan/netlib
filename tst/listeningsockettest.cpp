#include <stdio.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/Acceptor.h"
#include "Epoll.h"
#include "EpollRunner.h"
#include "SocketAddress.h"

using namespace EventLoop;
using namespace testing;

class ListenSocketTest: public Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
    EpollRunner runner;
    SocketAddress sa;
};

TEST_F(ListenSocketTest, create)
{


    Acceptor ls(&runner, sa);
	EXPECT_EQ(2, 2);
}



