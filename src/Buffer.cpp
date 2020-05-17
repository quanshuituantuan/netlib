#include <memory.h>
#include <assert.h>

#include "Buffer.h"

namespace EventLoop
{
    Buffer::Buffer():buffer_(nullptr), readIndex_(0), writeIndex_(0),capacity_(kInitialSize)
    {
        buffer_ = new char[kInitialSize];
        ::bzero(buffer_, 0);
    }

    void Buffer::append(Buffer &b)
    {
        int len = b.size();
        char *p = b.retrive(&len);
        append(p, len);
    }

    void Buffer::append(const char *data, int len)
    {
        int usedSize = capacity() - size();
        if(len >= usedSize)
        {
            resize();
        }

        if(readIndex_ <= writeIndex_ )
        {
            int firstCopySize = std::min(len, (capacity_ - writeIndex_));

            ::memcpy(buffer_+writeIndex_, data, firstCopySize);
            writeIndex_ = (writeIndex_ + firstCopySize) & (capacity_ - 1);

            int secondCopySize = len - firstCopySize;
            if(secondCopySize > 0)
            {
                ::memcpy(buffer_+writeIndex_, data + firstCopySize, secondCopySize);
                writeIndex_ = (writeIndex_ + secondCopySize) & (capacity_ - 1);
            }
        }
        else
        {
            ::memcpy(buffer_+writeIndex_, data, len);
            writeIndex_ = (writeIndex_ + len) & (capacity_ - 1);
        }
    }

    void Buffer::append(const std::string &data)
    {
        append(data.c_str(), data.size());
    }

    void Buffer::resize()
    {
        char *originalBuffer = buffer_;
        buffer_ = new char[capacity_*2];
        int originalSize = size();

        if(readIndex_ <= writeIndex_)
        {
            ::memcpy(buffer_, originalBuffer+readIndex_, originalSize);
        }
        else
        {
            ::memcpy(buffer_, originalBuffer+readIndex_, capacity_ - readIndex_);
            ::memcpy(buffer_ + capacity_ - readIndex_, originalBuffer, writeIndex_);
        }

        delete [] originalBuffer;
        readIndex_ = 0;
        writeIndex_ = originalSize;
        capacity_ *= 2;
    }

    char *Buffer::peek(int *len)
    {
        if(*len > size())
        {
            *len = 0;
            return nullptr;
        }

        if(writeIndex_ < readIndex_)
        {
            linearize();
        }

        return buffer_ + readIndex_;
    }

    char *Buffer::retrive(int *len)
    {
        if(*len > size())
        {
            *len = 0;
            return nullptr;
        }

        if(writeIndex_ < readIndex_)
        {
            linearize();
        }

        char *retBuf = peek(len);
        readIndex_ += *len;
        return retBuf;
    }

    int8_t Buffer::retrive(int8_t)
    {
        int len = 1;
        char *s = retrive(&len);
        assert(s);
        return static_cast<int8_t>(*s);
    }

    int16_t Buffer::retrive(int16_t)
    {
        int len = 2;
        char *s = retrive(&len);
        assert(s);
        return static_cast<int8_t>(*reinterpret_cast<int16_t*>(s));
    }

    int8_t Buffer::peek(int8_t)
    {
        int len = 1;
        char *s = peek(&len);
        assert(s);
        return static_cast<int8_t>(*s);
    }

    int16_t Buffer::peek(int16_t)
    {
        int len = 2;
        char *s = peek(&len);
        assert(s);
        return static_cast<int16_t>(*reinterpret_cast<int16_t*>(s));
    }

    void Buffer::linearize()
    {
        assert((writeIndex_ < readIndex_));
        char *originalBuffer = buffer_;
        buffer_ = new char[capacity_];
        ::memcpy(buffer_, originalBuffer+readIndex_, capacity_ - readIndex_);
        ::memcpy(buffer_ + capacity_ - readIndex_, originalBuffer, writeIndex_);
        delete [] originalBuffer;
        writeIndex_ = size();
        readIndex_ = 0;
    }

    //todo: need refactory this function
    void Buffer::swp(Buffer *buffer)
    {
        char *buf = this->buffer_;
        int readIndex = this->readIndex_;
        int writeIndex = this->writeIndex_;
        int capacity = this->capacity_;
        
        this->buffer_ = buffer->buffer_;
        this->readIndex_ = buffer->readIndex_;
        this->writeIndex_ = buffer->writeIndex_;
        this->capacity_ = buffer->capacity_;

        buffer->buffer_ = buf;
        buffer->readIndex_ = readIndex;
        buffer->writeIndex_ = writeIndex;
        buffer->capacity_ = capacity;
    }

    int Buffer::size() const 
    {
        return (capacity_ + (writeIndex_ - readIndex_)) & (capacity_ - 1);
    }

    Buffer::~Buffer()
    {
        delete [] buffer_;
    }

} /* namespace EventLoop */
