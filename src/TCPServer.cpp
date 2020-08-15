#include <iostream>
#include <utility>

#include "TCPServer.h"


namespace EventLoop
{
	TCPServer::TCPServer(Runner *runner, const SocketAddress &sa):
			runner_(runner),
			ls_(runner, sa)
	{
		ls_.setNewConnectionCb(std::bind(&TCPServer::newConnectionCb, this, std::placeholders::_1, std::placeholders::_2));
	}

	void TCPServer::newConnectionCb(int fd, const SocketAddress &peer)
	{
		// std::pair<FDMap::iterator, bool> ret(fdmap_.insert(std::make_pair(fd, e)));

		auto ret = connections_.insert(std::make_pair(fd, std::unique_ptr<Connection>(new Connection(runner_, fd, peer))));
		if(!ret.second)
		{
			std::cout<<"insert failed\n";
		}
		// connection_.reset(new Connection(runner_, fd, peer));
		connections_[fd]->setNewMessageCb(std::bind(&TCPServer::newMessageCb, this, fd, std::placeholders::_1));
		connections_[fd]->setCloseCb(std::bind(&TCPServer::closeConnectionCb, this, fd));
	}

	void TCPServer::newMessageCb(int fd, Buffer *buffer)
	{
		if(newMessageCb_)
		{
			auto it = connections_.find(fd);
			if(it != connections_.end())
			{
				newMessageCb_(&(*(it->second)), buffer);
			}
			
		}
	}

	void TCPServer::closeConnection(int fd)
	{
		std::cout<<"remove connection: "<<fd<<std::endl;
		connections_.erase(fd);
	}

	void TCPServer::closeConnectionCb(int fd)
	{
		runner_->addCallBack(std::bind(&TCPServer::closeConnection, this, fd));
	}
} /* namespace EchoServer */

