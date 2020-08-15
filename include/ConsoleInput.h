#ifndef THREADCPP_SRC_COMMON_CONSOLEINPUT_H_
#define THREADCPP_SRC_COMMON_CONSOLEINPUT_H_
#include <functional>

#include "EpollRunner.h"
#include "Runner.h"
#include "Epoll.h"
#include "Buffer.h"
#include "Context.h"

namespace EventLoop
{

    class ConsoleInput: public Context
    {
    public:
        typedef std::function<void (Buffer &buffer)> InputEventCb;

        ConsoleInput(Runner &runner, const InputEventCb &cb);

        ConsoleInput(const ConsoleInput &) = delete;

        ConsoleInput &operator = (const ConsoleInput &) = delete;

        int getFD() const ;


        ~ConsoleInput();

    private:
        // void handleEventCb(int fd, uint32_t event) override;
        Runner &runner_;
        InputEventCb inputEventCb_;
        Buffer buffer_;
        const static int BUFSIZE = 1024;
        int fd_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_SRC_COMMON_CONSOLEINPUT_H_ */
