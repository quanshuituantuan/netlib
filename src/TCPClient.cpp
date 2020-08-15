#include "TCPClient.h"

namespace EventLoop
{
TCPClient::TCPClient(Runner *runner, const SocketAddress &sa):
        runner_(runner),
        connector_(runner, sa)
{
    connector_.setConnectionEstablishCb(std::bind(&TCPClient::newConnectionCb, this, std::placeholders::_1, std::placeholders::_2));
}

void TCPClient::connect()
{
    connector_.connect();
}

void TCPClient::newConnectionCb(int fd, const SocketAddress &peer)
{
    // std::cout<<"before create AcceptSocket\n";
    connection_.reset(new Connection(runner_, fd, peer));
    connection_->setNewMessageCb(std::bind(&TCPClient::newMessageCb, this, std::placeholders::_1));
//    connection_->setMessageSendCb(std::bind(&Client::messageSendCB, this));
    connection_->setCloseCb(std::bind(&TCPClient::closeCB, this));

    if(newConnectionCb_)
    {
        newConnectionCb_();
    }
}

void TCPClient::closeCB()
{
	std::cout<<"connection close"<<std::endl;
}

void TCPClient::send(Buffer *buffer)
{
    connection_->send(buffer);
}

void TCPClient::close()
{
    connection_->close();
}

void TCPClient::newMessageCb(Buffer *buffer)
{
    if(newMessageCb_)
    {
        newMessageCb_(&(*connection_), buffer);
    }
}

} /* namespace EventLoop */
