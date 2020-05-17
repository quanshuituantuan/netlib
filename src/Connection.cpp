#include "Epoll.h"
#include "Runner.h"
#include "SocketAddress.h"

#include "Connection.h"

namespace EventLoop
{
    Connection::Connection(Runner *runner, int fd, const SocketAddress &peer):
            runner_(runner), socket_(fd), connectionClosed_(false)
    {
        std::cout<<"connection socket from "<<peer.toString()<<std::endl;
        std::cout<<"fd: "<<socket_.fd()<<std::endl;
        socket_.setNoneBlock();
        runner_->addFDListener(socket_.fd(), *this, EpollEvent::kEventIn | EpollEvent::kEventOut | EpollEvent::kEventLT);
    }

    void Connection::close()
    {
        if(!connectionClosed_)
        {
            std::cout<<"close connection\n";
            runner_->delFDListener(socket_.fd());
            socket_.shutdown(How::DiableReadWrite);
            connectionClosed_ = true;

            if(closeCb_)
            {
                closeCb_();
            }
        }
    }

    Connection::~Connection()
    {
        close();
    }

    void Connection::handleInput()
    {
        try
        {
            socket_.recv(&recvBuffer_);
        }
        catch(const std::exception &e)
        {
            std::cout<<"start to close connection\n";
            std::cout<<e.what()<<std::endl;
            close();
            return;
        }
        if(newMessageCb_)
        {
            newMessageCb_(&recvBuffer_);
        }
    }

    void Connection::handleOutput()
    {
        
        if(sendBuffer_.size() > 0)
        {
            socket_.send(&sendBuffer_);
        }
        else 
        {
            if(messageSendCb_)
            {
                messageSendCb_();
            }
            //disable eventOut, which mean send buf is empty.
            runner_->modifyFDListener(socket_.fd(), EpollEvent::kEventIn);
        }
        
    }

    void Connection::handleClose()
    {
        close();
    }

    void Connection::handleError()
    {
        std::string s("error");
        if (errorCb_) errorCb_(s);
        close();
    }

    void Connection::send(Buffer *buffer)
    {
        //enable eventOut, if send buf become empty, then event will happen.
        runner_->modifyFDListener(socket_.fd(), EpollEvent::kEventIn | EpollEvent::kEventOut | EpollEvent::kEventLT);
        
        //todo: this is bug, sendbuffer may not empty, some data will lost. 
        sendBuffer_.append(*buffer);

        //socket_.send(&sendBuffer_);
    }
} /* namespace EventLoop */
