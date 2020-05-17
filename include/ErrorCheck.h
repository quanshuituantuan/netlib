#ifndef THREADCPP_ERRORCHECK_H_
#define THREADCPP_ERRORCHECK_H_
#include <errno.h>
#include <string.h>

#include <string>
#include <exception>
#include <sstream>
#include <iostream>

namespace EventLoop
{
    class ReturnErrorException: public std::runtime_error
    {
    public:
        explicit ReturnErrorException(const std::string &s):
            runtime_error(s)
        {
        }

        ~ReturnErrorException() = default;
    };

    #define THROWEXCEPTION(file, line, function, ret) \
                std::string s("Error happens at "); \
                std::ostringstream line_str, error; \
                line_str<<line; \
                error<<ret; \
                error<<::strerror(errno);\
                s +="file: "; \
                s += file; \
                s += ", "; \
                s += "line: "; \
                s += line_str.str(); \
                s += ", "; \
                s +="function: "; \
                s += function; \
                s += ", "; \
                s += "error code: "; \
                s += error.str(); \
                s += "."; \
                std::cout<<s<<std::endl; \
                throw(ReturnErrorException(s));

    #define TCHECK(ret) \
                if(ret != 0) { \
                    THROWEXCEPTION(__FILE__, __LINE__, __func__, ret); \
                }

    template<typename Func, typename ... Args>
    int failAndRetry(Func f, Args ... args)
    {
        int ret(0);
        do {
            ret = f(args ...);
        }while((ret<0) && (ret == EINTR));

        return ret;
    }
}
#endif /* THREADCPP_ERRORCHECK_H_ */
