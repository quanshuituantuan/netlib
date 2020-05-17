#ifndef THREADCPP_SRC_COMMON_TIMEQUEUE_H_
#define THREADCPP_SRC_COMMON_TIMEQUEUE_H_
#include <list>
#include <functional>
#include <map>
#include <queue>
#include <utility>

#include "CallBackQueue.h"

namespace EventLoop
{
    class TimeoutQueue
    {
    public:
        typedef std::function<void (void)> CallBack;

        struct Timeout
        {
            Timeout(int timeout, const CallBack &cb):
                timeout_(timeout), cb_(cb)
            {
            }

            int timeout_;
            CallBack cb_;
        };

        typedef std::priority_queue<Timeout, std::vector<Timeout>, std::greater<Timeout>> Timeouts;

        TimeoutQueue();

        TimeoutQueue(const TimeoutQueue &) = delete;

        TimeoutQueue &operator = (const TimeoutQueue &) = delete;

        void schedule(int timeout, const CallBack &cb);

        //execute all timeout event, timeout value = 0
        void run();

        //here timeout value is milisecond
        void elapse(int time);

        int count();

        ~TimeoutQueue();
    private:
        Timeouts timeouts_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_SRC_COMMON_TIMEQUEUE_H_ */
