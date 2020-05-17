#include <gtest/gtest.h>

#include "FDMapping.h"

using namespace EventLoop;
using namespace testing;

class FDMappingTest: public Test
{

};

TEST_F(FDMappingTest, create)
{
    FDMapping fdmapping;
}

TEST_F(FDMappingTest, add)
{
    FDMapping fdmapping;
    int fd(0);
    Context *fdlistener(nullptr);
    uint32_t event(0);

    fdmapping.add(fd, fdlistener, event);
    EXPECT_EQ(1, fdmapping.count());
}

TEST_F(FDMappingTest, addAlreadyExist)
{
    FDMapping fdmapping;
    int fd(0);
    Context *fdlistener(nullptr);
    uint32_t event(1);

    fdmapping.add(fd, fdlistener, event);
    event = 2;
    fdmapping.add(fd, fdlistener, event);

    EXPECT_EQ(1, fdmapping.count());
    EXPECT_EQ(1|2, fdmapping.getEvent(fd));
}

TEST_F(FDMappingTest, modify)
{
    FDMapping fdmapping;
    int fd(0);
    Context *fdlistener(nullptr);
    uint32_t event(1);

    fdmapping.add(fd, fdlistener, event);
    event = 2;
    fdmapping.modify(fd, event);

    EXPECT_EQ(1, fdmapping.count());
    EXPECT_EQ(2, fdmapping.getEvent(fd));
}

TEST_F(FDMappingTest, delTest)
{
    FDMapping fdmapping;
    int fd(0);
    Context *fdlistener(nullptr);
    uint32_t event(1);

    fdmapping.add(fd, fdlistener, event);
    fdmapping.del(fd);

    EXPECT_EQ(0, fdmapping.count());
}
