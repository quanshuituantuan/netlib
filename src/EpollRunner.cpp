#include "EpollRunner.h"

namespace EventLoop
{
    int EpollRunner::TIMEOUT(10);
    EpollRunner::EpollRunner()
    {
    }

    EpollRunner::~EpollRunner()
    {
    }

    void EpollRunner::run()
    {

        run([](){ return true;});

    }

    void EpollRunner::run(const Continue &c)
    {
        while(true) {
            cbQueue_.run();
            timeoutQueue_.elapse(TIMEOUT);
            timeoutQueue_.run();

            int eventsNum = epoll_.wait(TIMEOUT);
            if(!eventsNum) {
                continue ;
            }

            /**
             * todo: need resize epoll_, or it will always increase
             */
            int loop(0);
            Epoll::event_iterator i=epoll_.begin();
            while(loop++ < eventsNum)
            {
                Context &fdlistener (fdMapping_.getFDListener(i->data.fd));
                fdlistener.handleEvent(i->data.fd, i->events);
                ++i;
            }
            
            if(!c())
            {
                break;
            }
        }
    }

    void EpollRunner::addCallBack(const CallBack &cb)
    {
        cbQueue_.schedule(cb);
    }

    void EpollRunner::addFDListener(int fd, Context &fdlistener, uint32_t event)
    {
        epoll_.add(fd, event);
        fdMapping_.add(fd, &fdlistener, event);
    }

    void EpollRunner::delFDListener(int fd)
    {
        epoll_.del(fd, fdMapping_.getEvent(fd));
        fdMapping_.del(fd);
    }

    void EpollRunner::modifyFDListener(int fd, uint32_t event)
    {
        epoll_.modify(fd, event);
        fdMapping_.modify(fd, event);
    }

    void EpollRunner::scheduleTimeout(int time, const CallBack &cb)
    {
        timeoutQueue_.schedule(time, cb);
    }
} /* namespace EventLoop */
