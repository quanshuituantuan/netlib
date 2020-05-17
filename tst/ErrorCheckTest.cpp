#include <stdio.h>

#include <iostream>
#include <gtest/gtest.h>

#include "ErrorCheck.h"

using namespace EventLoop;

int ok(bool status)
{
    if(status)
        return 0;

    return -1;
}

int dumyRetry()
{
    static int i = EINTR;
    i++;
    return i;
}

TEST(ErrorCheck, ok)
{
    TCHECK(ok(true));
}

//TEST(ErrorCheck, nok)
//{
//    EXPECT_THROW(TCHECK(ok(false)), ReturnErrorException);
//}

TEST(ErrorCheck, nokPrint)
{
    try {
        TCHECK(ok(false));
    }
    catch (ReturnErrorException &e) {
        std::cout<<e.what()<<std::endl;
    }
}

TEST(ErrorCheck, true)
{
    EXPECT_TRUE(true);
}

TEST(ErrorCheck, retry)
{
    int ret(0);
    ret = failAndRetry(dumyRetry);
    EXPECT_EQ(ret, EINTR+1);
}
