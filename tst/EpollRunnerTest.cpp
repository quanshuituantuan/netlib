#include <gtest/gtest.h>
#include <iostream>

#include "ConsoleInput.h"
#include "EpollRunner.h"
#include "Buffer.h"

using namespace EventLoop;
using namespace testing;

class EpollRunnerTest: public Test
{

};

void sum(int &value)
{
    value++;
}

void print()
{
    std::cout<<"this is only test"<<std::endl;
}
//
//void inputHandler(const Buffer &buffer)
//{
//    int size(0);
//    std::cout<<"Get input: "<<std::string(buffer.getData(size), buffer.getUsedSize())
//            <<" size: "<<size<<std::endl;
//}

TEST_F(EpollRunnerTest, create)
{
    EpollRunner runner;
}

//TEST_F(EpollRunnerTest, addCallBack)
//{
//    EpollRunner runner;
//    int value(0);
//
//    runner.addCallBack(std::bind(sum, std::ref(value)));
//    runner.addCallBack(std::bind(sum, std::ref(value)));
//    runner.run();
//
//    EXPECT_EQ(2, value);
//}

//TEST_F(EpollRunnerTest, addTimeout)
//{
//    EpollRunner runner;
//    int value(0);
//
//    runner.scheduleTimeout(0, std::bind(sum, std::ref(value)));
//    runner.scheduleTimeout(1, std::bind(sum, std::ref(value)));
//    runner.scheduleTimeout(2, std::bind(sum, std::ref(value)));
//    runner.scheduleTimeout(40, std::bind(sum, std::ref(value)));
//    runner.run();
//
//    EXPECT_EQ(3, value);
//}

//TEST_F(EpollRunnerTest, consoleInputEvent)
//{
//    EpollRunner runner;
//    ConsoleInput input(runner, inputHandler);
//    runner.addCallBack(std::bind(print));
//    runner.scheduleTimeout(1000, std::bind(print));
//    runner.run();
//}


