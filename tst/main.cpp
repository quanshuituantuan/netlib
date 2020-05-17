#include <iostream>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    std::cout<<"start gtest case ......\n"<<std::endl;
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}




