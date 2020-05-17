#include <gtest/gtest.h>

#include <Buffer.h>

using namespace testing;
using namespace EventLoop;

class BufferTest: public Test
{

};

TEST_F(BufferTest, create)
{
    Buffer buffer();
}
/*
TEST_F(BufferTest, usedSize)
{
    Buffer buffer;
    std::string s1("111111");

    buffer.appendData(s1);

    EXPECT_EQ(s1.size(), buffer.getUsedSize());
}

TEST_F(BufferTest, appendData)
{
    Buffer buffer;
    std::string s1("111111");

    buffer.appendData(s1);

    int size(0);
    buffer.getData(size);
    std::string data(buffer.getData(size), size);
    EXPECT_STREQ(s1.c_str(), data.c_str());
}

TEST_F(BufferTest, appendTwoData)
{
    Buffer buffer;
    std::string s1("55555");
    std::string s2("88888888");
    std::string s3=s1+s2;

    buffer.appendData(s1);
    buffer.appendData(s2);

    EXPECT_EQ(s3.size(), buffer.getUsedSize());
    int size(0);
    EXPECT_STREQ(s3.c_str(), std::string(buffer.getData(size), buffer.getUsedSize()).c_str());
}
*/
TEST_F(BufferTest, size)
{
    Buffer buffer;


    EXPECT_EQ(0, buffer.size());
}

TEST_F(BufferTest, append)
{
    Buffer buffer;
    std::string s1("55555");

    buffer.append(s1);

    EXPECT_EQ(5, buffer.size());
}

TEST_F(BufferTest, capacity)
{
    Buffer buffer;

    EXPECT_EQ(1024, buffer.capacity());
    buffer.resize();
    EXPECT_EQ(1024*2, buffer.capacity());
    buffer.resize();
    EXPECT_EQ(1024*2*2, buffer.capacity());
}
/*
TEST_F(BufferTest, linearizeIternal)
{
    Buffer buffer;
    std::string first("aaaaa");
    std::string second("helloworld");
    std::string expected=second + first;
    memcpy(buffer.buffer_, first.c_str(), 5);

    buffer.writeIndex_ = 5;
    buffer.readIndex_ = buffer.capacity()-10;
    memcpy(buffer.buffer_+buffer.readIndex_, second.c_str(), 10);

    buffer.linearize();

    EXPECT_EQ(0, buffer.readIndex_);
    EXPECT_EQ(15, buffer.writeIndex_);
    EXPECT_STREQ(buffer.buffer_, expected.c_str());
}
*/
/*
TEST_F(BufferTest, resizeIternal)
{
    Buffer buffer;
    std::string first("aaaaa");
    std::string second("helloworld");
    std::string expected=second + first;
    memcpy(buffer.buffer_, first.c_str(), 5);

    buffer.writeIndex_ = 5;
    buffer.readIndex_ = buffer.capacity()-10;
    memcpy(buffer.buffer_+buffer.readIndex_, second.c_str(), 10);

    buffer.resize();

    EXPECT_EQ(0, buffer.readIndex_);
    EXPECT_EQ(15, buffer.writeIndex_);
    EXPECT_EQ(1024*2, buffer.capacity());
    EXPECT_STREQ(buffer.buffer_, expected.c_str());
}
*/

TEST_F(BufferTest, appendTwoString)
{
    Buffer buffer;
    std::string first("aaaaa");
    std::string second("helloworld");
    std::string expected=first + second;

    buffer.append(first);
    buffer.append(second);

    int len = buffer.size();
    EXPECT_EQ(15, len);

//    EXPECT_STREQ(buffer.buffer_, expected.c_str());
}

TEST_F(BufferTest, retrive)
{
    Buffer buffer;
    std::string first("aaaaa");
    std::string second("helloworld");
    std::string expected=first + second;

    buffer.append(first);
    buffer.append(second);

    int len(5);
    char *s1 = buffer.retrive(&len);
    std::string ss1(s1, len);
    EXPECT_EQ(5, len);
    EXPECT_EQ(first, ss1);

    len = 10;
    s1 = buffer.retrive(&len);
    std::string ss2(s1, len);
    EXPECT_EQ(10, len);
    EXPECT_EQ(second, ss2);
}

TEST_F(BufferTest, retriveFailLenTooBig)
{
    Buffer buffer;
    std::string first("aaaaa");

    buffer.append(first);

    int len(10);
    char *s1 = buffer.retrive(&len);
    std::string ss1(s1, len);
    EXPECT_EQ(0, len);
    EXPECT_EQ(nullptr, s1);
}

TEST_F(BufferTest, retriveInt8)
{
    Buffer buffer;
    int8_t v = 10;

    buffer.append(reinterpret_cast<char*>(&v));

    int8_t len(1);
    int8_t ret = buffer.retrive(len);
    EXPECT_EQ(v, ret);
    EXPECT_EQ(0, buffer.size());
}

TEST_F(BufferTest, retriveInt16)
{
    Buffer buffer;
    int16_t v = 10;

    buffer.append(reinterpret_cast<char*>(&v), 2);

    int16_t len(1);
    int16_t ret = buffer.retrive(len);
    EXPECT_EQ(v, ret);
    EXPECT_EQ(0, buffer.size());
}

TEST_F(BufferTest, peekInt8)
{
    Buffer buffer;
    int8_t v = 10;

    buffer.append(reinterpret_cast<char*>(&v));

    int8_t len(1);
    int8_t ret = buffer.peek(len);
    EXPECT_EQ(v, ret);
    EXPECT_EQ(1, buffer.size());
}

TEST_F(BufferTest, peekInt16)
{
    Buffer buffer;
    int16_t v = 10;

    buffer.append(reinterpret_cast<char*>(&v), 2);

    int16_t len(1);
    int16_t ret = buffer.peek(len);
    EXPECT_EQ(v, ret);
    EXPECT_EQ(2, buffer.size());
}

TEST_F(BufferTest, swp)
{
    Buffer b1, b2;
    b1.append("hello");
    EXPECT_EQ(5, b1.size());
    b1.swp(&b2);

    EXPECT_EQ(5, b2.size());
}

TEST_F(BufferTest, appendBuffer)
{
    Buffer b1, b2;

    b1.append("hello");
    b2.append(" lili");
    b1.append(b2);

    int i=10;
    EXPECT_EQ(10, b1.size());
    EXPECT_EQ("hello lili", b1.retrive(&i));
}
