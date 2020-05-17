#ifndef THREADCPP_SRC_COMMON_BUFFER_H_
#define THREADCPP_SRC_COMMON_BUFFER_H_
#include <string>
#include <vector>
#include <iostream>
#include "NoneCopyable.h"

namespace EventLoop
{
    class Buffer: public NoneCopyable
    {
    public:
        /**
         * initial size shall always 2^n
         */
    	const static int kInitialSize = 1024;

        Buffer();

        Buffer(const Buffer &) = default;

        Buffer &operator = (const Buffer &) = default;

        void append(Buffer &);

        void append(const char *data, int len);

        void append(const std::string &data);

        char *peek(int *len);

        char *retrive(int *len);

        int8_t retrive(int8_t);

        int16_t retrive(int16_t);

        int8_t peek(int8_t);

        int16_t peek(int16_t);

        void linearize();

        int size() const;

        int capacity() const
        {
            return capacity_;
        }

        void resize();

        void swp(Buffer *buffer);
        
        ~Buffer();

    private:
        char *buffer_;
        int readIndex_;
        int writeIndex_;
        int capacity_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_SRC_COMMON_BUFFER_H_ */
