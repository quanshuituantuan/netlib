#include "Epoll.h"

#include "Context.h"

namespace EventLoop
{
    void Context::handleEvent(int , uint32_t events)
    {

        //  std::cout<<"handle event: "<<eventsToString(fd, events)<<std::endl;
        if (events & (EpollEvent::kEventIn | EpollEvent::kEventPriority | EpollEvent::kEventHup))
        {
            try {
                handleInput();
            }
            catch(const std::exception &e)
            {
                std::cout<<"catch exception, try to close connection: "<<e.what()<<std::endl;
                handleClose();
            }
        }
        if (events & EpollEvent::kEventOut)
        {
            try {
                handleOutput();
            }
            catch(const std::exception &e)
            {
                std::cout<<"catch exception, try to close connection: "<<e.what()<<std::endl;
                handleClose();
            }
        }
        if ((events & EpollEvent::kEventHup) && !(events & EpollEvent::kEventIn))
        {
            handleClose();
        }
        if (events & (EpollEvent::kEventErr))
        {
            handleError();
        }
    }

    void Context::handleInput()
    {

    }

    void Context::handleOutput()
    {

    }

    void Context::handleClose()
    {

    }

    void Context::handleError()
    {

    }


    Context::~Context()
    {
    }

} /* namespace EventLoop */
