#ifndef THREADCPP_SRC_COMMON_CALLBACK_H_
#define THREADCPP_SRC_COMMON_CALLBACK_H_
#include <list>
#include <functional>

namespace EventLoop
{

    class CallBackQueue
    {
    public:
        typedef std::function<void (void)> CallBack;

        CallBackQueue();

        CallBackQueue(const CallBackQueue &) = delete;

        CallBackQueue &operator = (const CallBackQueue &) = delete;

        void schedule(const CallBack &cb);

        void run();

        int count();

        ~CallBackQueue();
    private:
        std::list<CallBack> cbQueue_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_SRC_COMMON_CALLBACK_H_ */
