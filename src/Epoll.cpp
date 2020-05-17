#include "ErrorCheck.h"

#include "Epoll.h"

namespace EventLoop
{
    std::string eventsToString(int fd, int ev)
    {
      std::ostringstream oss;
      oss << fd << ": ";
      if (ev & EPOLLIN)
        oss << "IN ";
      if (ev & EPOLLPRI)
        oss << "PRI ";
      if (ev & EPOLLOUT)
        oss << "OUT ";
      if (ev & EPOLLHUP)
        oss << "HUP ";
      if (ev & EPOLLRDHUP)
        oss << "RDHUP ";
      if (ev & EPOLLERR)
        oss << "ERR ";

      return oss.str().c_str();
    }

    Epoll::Epoll():
            epfd_(::epoll_create(1)),
            count_(0)
    {
    }

    void Epoll::add(int fd, uint32_t event)
    {
        struct epoll_event e;
        e.events = event;
        e.data.fd=fd;

        TCHECK(::epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &e));
        count_++;
    }

    void Epoll::modify(int fd, uint32_t event)
    {
        struct epoll_event e;
        e.events = event;
        e.data.fd = fd;

        TCHECK(::epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &e));
    }

    void Epoll::del(int fd, uint32_t event)
    {
        struct epoll_event e;
        e.events = event;
        e.data.fd = fd;

        TCHECK(::epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, &e));
        count_--;
    }

    int Epoll::wait(int timeout)
    {
        if(count_ == 0) {
            ::usleep(static_cast<unsigned int>(timeout));
            return 0;
        }

        events_.resize(count_);
        int ret = ::epoll_wait(epfd_, &events_[0], events_.size(), timeout);
        if(ret < 0) {
            throw EpollWaitingFailing(strerror(errno));
        }
        return ret;
    }

    Epoll::event_iterator Epoll::begin()
    {
        return events_.begin();
    }

    Epoll::event_iterator Epoll::end()
    {
        return events_.end();
    }

    Epoll::~Epoll()
    {
    }

} /* namespace EventLoop */
