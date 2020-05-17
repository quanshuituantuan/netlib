#include <stdio.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Epoll.h"

using namespace EventLoop;
using namespace testing;

class EpollTest: public Test
{
protected:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// TEST_F(EpollTest, EpollAdd)
// {
//     SystemMock s;

//     EXPECT_CALL(s, epollCreate()).Times(1);
//     EXPECT_CALL(s, epollCtl(_, _, _,_)).Times(1).WillOnce(Return(0));

//     Epoll p(s);
//     p.add(1, EpollEvent::kEventIn);
// }

//TEST_F(EpollTest, EpollAddNoMock)
//{
//    Epoll p(System::getSystem());
//    p.add(STDIN_FILENO, Epoll::EVENT_IN);
//    int ret = p.wait(2000);
//    ret = ret;
//    std::cout<<"ret "<<ret<<std::endl;
//}

//TEST_F(EpollTest, EpollCount)
//{
//    SystemMock s;
//
//    EXPECT_CALL(s, epollCtl(_, _, _,_)).Times(2).WillOnce(Return(0)).WillOnce(Return(0));
//    EXPECT_CALL(s, epollWait(_, _, _, _)).Times(1).WillOnce(Return(2));
//
//    Epoll p(s);
//    p.add(1, Epoll::EVENT_IN);
//    p.add(1, Epoll::EVENT_OUT);
//
//    p.wait(0);
//    Epoll::event_iterator iter = p.begin();
//    int count = 0;
//    while(iter++ != p.end()) {
//        count++;
//    }
//    EXPECT_EQ(count, 2);
//}


