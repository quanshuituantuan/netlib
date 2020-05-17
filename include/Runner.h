#ifndef SRC_EPOLLRUNNERBASE_H_
#define SRC_EPOLLRUNNERBASE_H_
#include <functional>

#include "Context.h"

namespace EventLoop
{
    class Runner
    {
    public:
        typedef std::function<bool()> Continue;
        typedef std::function<void (void)> CallBack;

        Runner();

        virtual ~Runner();

        virtual void run() = 0;

        virtual void run(const Continue &con) = 0;

        virtual void addFDListener(int fd, Context &fdlistener, uint32_t event) = 0;

        virtual void modifyFDListener(int fd, uint32_t event) = 0;

        virtual void delFDListener(int fd) = 0;

        virtual void addCallBack(const CallBack &cb) = 0;

        virtual void scheduleTimeout(int time, const CallBack &cb) = 0;
    };

} /* namespace EventLoop */

#endif /* SRC_EPOLLRUNNERBASE_H_ */
