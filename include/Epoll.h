#ifndef THREADCPP_SRC_COMMON_EPOLL_H_
#define THREADCPP_SRC_COMMON_EPOLL_H_
#include <errno.h>
#include <string.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>

#include <vector>
#include <string>
#include <exception>
#include <stdexcept>

#include "NoneCopyable.h"

namespace EventLoop
{
    
    namespace  EpollEvent
	{
		const uint32_t kEventIn = EPOLLIN;
		const uint32_t kEventOut = EPOLLOUT;
		const uint32_t kEventPriority = EPOLLPRI;
		const uint32_t kEventHup = EPOLLRDHUP;
		const uint32_t kEventErr = EPOLLERR;
		const uint32_t kEventET = EPOLLET;
        const uint32_t kEventLT = 0;
	};

	std::string eventsToString(int fd, int ev);
    
    class Epoll: public NoneCopyable
    {
    public:
        class EpollWaitingFailing: public std::runtime_error
        {
        public:
            EpollWaitingFailing(const std::string &s):runtime_error(s)
            {
            }
        };

        typedef std::vector<struct epoll_event> EpollEvents;
        typedef EpollEvents::const_iterator event_iterator;

        Epoll();

        ~Epoll();

        void add(int fd, uint32_t event);

        void modify(int fd, uint32_t event);

        void del(int fd, uint32_t event);

        int wait(int timeout);

        event_iterator begin();

        event_iterator end();

    private:
        int epfd_;
        int count_;
        EpollEvents events_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_SRC_COMMON_EPOLL_H_ */
