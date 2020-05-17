#include <stdio.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SocketAddress.h"

using namespace EventLoop;
using namespace testing;

class SocketAddressTest: public Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

TEST_F(SocketAddressTest, create)
{
	SocketAddress sockAddr("1.1.1.1", 111, false);
	EXPECT_EQ(2, 2);
}

TEST_F(SocketAddressTest, toString)
{
	SocketAddress sockAddr("1.1.1.1", 111, false);
	std::string expected("1.1.1.1:111");

	std::string s = sockAddr.toString();
	EXPECT_EQ(s, expected);
}

TEST_F(SocketAddressTest, setAddress)
{
    SocketAddress sockAddr;
    int port  = 5000;
    std::string expected("127.0.0.1:5000");

    struct sockaddr sa;
    struct sockaddr_in *in = (struct sockaddr_in *)&sa;

    in->sin_family = AF_INET;
    in->sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &(in->sin_addr));
    sockAddr.setAddress(sa);
    std::string s = sockAddr.toString();
    EXPECT_EQ(s, expected);
}


