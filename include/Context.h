#ifndef THREADCPP_SRC_COMMON_FDLISTENER_H_
#define THREADCPP_SRC_COMMON_FDLISTENER_H_
#include <stdint.h>
#include <exception>

#include "Buffer.h"
#include "Epoll.h"


namespace EventLoop
{
    class ContextError: public std::runtime_error
    {
    public:
        explicit ContextError(const std::string &msg): std::runtime_error(msg)
        {

        }
    };

    class Context
    {
    public:
        Context() = default;

        Context(const Context &) = delete;

        Context &operator = (const Context &) = delete;

        void handleEvent(int fd, uint32_t events);

        virtual ~Context() = 0;
    private:

        virtual void handleInput() ;

        virtual void handleOutput() ;

        virtual void handleClose() ;

        virtual void handleError() ; 
        
    };

} /* namespace EventLoop */

#endif /* THREADCPP_SRC_COMMON_FDLISTENER_H_ */
