#include "CallBackQueue.h"

namespace EventLoop
{

    CallBackQueue::CallBackQueue()
    {
    }

    CallBackQueue::~CallBackQueue()
    {
    }

    void CallBackQueue::schedule(const CallBack &cb)
    {
        cbQueue_.push_back(cb);
    }

    void CallBackQueue::run()
    {
        for(const auto &i: cbQueue_) {
            (i)();
        }
        cbQueue_.clear();
    }

    int CallBackQueue::count()
    {
        return cbQueue_.size();
    }
} /* namespace EventLoop */
