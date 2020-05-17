#include <algorithm>
#include <iostream>

#include "TimeoutQueue.h"

namespace EventLoop
{
    bool operator < (const TimeoutQueue::Timeout &value1, const TimeoutQueue::Timeout &value2)
    {
        return value1.timeout_ < value2.timeout_;
    }

    bool operator > (const TimeoutQueue::Timeout &value1, const TimeoutQueue::Timeout &value2)
    {
        return value1.timeout_ > value2.timeout_;
    }

    TimeoutQueue::TimeoutQueue()
    {
    }

    void TimeoutQueue::schedule(int timeout, const CallBack &cb)
    {
        timeouts_.push(Timeout(timeout, cb));
    }

    void TimeoutQueue::run()
    {
        while(!timeouts_.empty() && !timeouts_.top().timeout_) {
            timeouts_.top().cb_();
            timeouts_.pop();
        }
    }

    void TimeoutQueue::elapse(int time)
    {
        std::priority_queue<Timeout, std::vector<Timeout>, std::less<Timeout>> temp;

        while(!timeouts_.empty()) {
            Timeout t = timeouts_.top();
            timeouts_.pop();
            t.timeout_ = std::max(t.timeout_ - time, 0);
            temp.push(t);
        }

        while(!temp.empty()) {
            timeouts_.push(temp.top());
            temp.pop();
        }
    }

    int TimeoutQueue::count()
    {
        return timeouts_.size();
    }

    TimeoutQueue::~TimeoutQueue()
    {
    }

} /* namespace EventLoop */
