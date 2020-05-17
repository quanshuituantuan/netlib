#ifndef THREADCPP_SRC_COMMON_EPOLLRUNNER_H_
#define THREADCPP_SRC_COMMON_EPOLLRUNNER_H_
#include <functional>

#include "Runner.h"
#include "CallBackQueue.h"
#include "Context.h"
#include "TimeoutQueue.h"
#include "FDMapping.h"

namespace EventLoop
{
    class EpollRunner: public Runner
    {
    public:
        typedef std::function<bool()> Continue;
        typedef std::function<void ()> CallBack;

        EpollRunner();

        EpollRunner(const EpollRunner &) = delete;

        EpollRunner &operator = (const EpollRunner &) = delete;

        void run() override;

        void run(const Continue &cont);

        void addFDListener(int fd, Context &fdlistener, uint32_t event) override;

        void modifyFDListener(int fd, uint32_t event) override;

        void delFDListener(int fd) override;

        void addCallBack(const CallBack &cb) override;

        void scheduleTimeout(int time, const CallBack &cb) override;

        ~EpollRunner();

    private:
        CallBackQueue   cbQueue_;
        TimeoutQueue    timeoutQueue_;
        Epoll  			epoll_;
        FDMapping 		fdMapping_;
        static int      TIMEOUT;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_SRC_COMMON_EPOLLRUNNER_H_ */
