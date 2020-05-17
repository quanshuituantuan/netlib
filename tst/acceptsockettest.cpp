
#include <stdio.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../include/Connection.h"
#include "Epoll.h"
#include "EpollRunner.h"
#include "SocketAddress.h"

using namespace EventLoop;
using namespace testing;

class acceptsockettest: public Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(acceptsockettest, create)
{
    SocketAddress sa;
    EpollRunner runner;
    Connection as(&runner, Socket::create(AF_INET, SOCK_STREAM, 0), sa);


    EXPECT_EQ(2, 2);
}



