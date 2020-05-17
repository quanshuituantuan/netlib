#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

#include "EpollRunner.h"

#include "Acceptor.h"

namespace EventLoop
{
    Acceptor::Acceptor(Runner *runner, const SocketAddress &sockAddr):
            runner_(runner),
            sa_(sockAddr),
            socket_(Socket::create(AF_INET))
    {
        std::cout<<"Listen on "<<sockAddr.toString()<<" fd: "<<socket_.fd()<<std::endl;
        socket_.setReuseAddr(true);
        socket_.bind(sockAddr);
        socket_.listen();
        runner_->addFDListener(socket_.fd(), *this, EpollEvent::kEventIn);
    }

    Acceptor::~Acceptor()
    {
        runner_->delFDListener(socket_.fd());
    }

    void Acceptor::handleInput()
    {
            SocketAddress sa;
            int newFD = socket_.accept(&sa);
            if(newConnectionCb_)
            {
                newConnectionCb_(newFD, sa);
            }
    }

    void Acceptor::handleOutput()
    {
        //listening socket will not send any msg, it just accept connection
    }

    void Acceptor::handleClose()
    {
        //listening socket will not close
    }

    void Acceptor::handleError()
    {
        //todo: here may need print some log to indicate some socket connection reject. 
    }
} /* namespace EventLoop */
