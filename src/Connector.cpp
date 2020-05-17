#include "EpollRunner.h"
#include "Connector.h"

namespace EventLoop
{

    Connector::Connector(Runner *runner, const SocketAddress &sa):
            runner_(runner), peer_(sa), socket_(Socket::create(AF_INET)), connected_(false)
    {
        socket_.setNoneBlock();
        runner_->addFDListener(socket_.fd(), *this,  EpollEvent::kEventOut);
    }

    void Connector::connect()
    {
        socket_.connect(socket_.fd(), peer_);
    }

    void Connector::setConnectionEstablishCb(const ConnectionEstablishCb &cb)
    {
        connectionEstablishCb_ = cb;
    }

    void Connector::handleInput()
    {

    }

    void Connector::handleOutput()
    {
            if(!connected_)
            {
                runner_->delFDListener(socket_.fd());
                connectionEstablishCb_(socket_.fd(), peer_);
                connected_ = true;
            }
    }

    void Connector::handleClose()
    {

    }

    void Connector::handleError()
    {

    }
    
    Connector::~Connector()
    {
        /**
         * connector no need remove listener from FDMapping, as connection object
         * use the same fd as connector. Finally Connection object will remove fd
         * from FDMapping.
         */
    }

} /* namespace EventLoop */
