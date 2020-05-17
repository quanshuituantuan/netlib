#include <stdio.h>
#include <unistd.h>

#include "Epoll.h"
#include "ConsoleInput.h"

namespace EventLoop
{
    const int ConsoleInput::BUFSIZE;
    ConsoleInput::ConsoleInput(Runner &runner, const InputEventCb &cb):
            runner_(runner),
            inputEventCb_(cb),
            fd_(STDIN_FILENO)
    {
        runner_.addFDListener(this->getFD(), *this, EpollEvent::kEventIn);
    }

    int ConsoleInput::getFD() const
    {
        return fd_;
    }

    ConsoleInput::~ConsoleInput()
    {
        runner_.delFDListener(getFD());
    }

} /* namespace EventLoop */
