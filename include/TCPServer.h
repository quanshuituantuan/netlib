#ifndef NEWEXAMPLES_SERVER_H_
#define NEWEXAMPLES_SERVER_H_

#include <functional>
#include <memory>
#include <map>

#include "Acceptor.h"
#include "Connection.h"
#include "Buffer.h"
#include "Runner.h"
#include "EpollRunner.h"

namespace EventLoop
{
	class TCPServer
	{
		public:
			typedef std::function<void (Connection *connection, Buffer *buffer)> NewMessageCb;
			typedef std::map<int, std::unique_ptr<Connection>>	Map;

			TCPServer(Runner *runner, const SocketAddress &sa);

			void setNewMessageCb(const NewMessageCb &cb)
			{
				newMessageCb_ = cb;
			}

			~TCPServer(){
				std::cout<<"destroy server\n";
			}

			void closeConnection(int fd);

		private:

			void closeConnectionCb(int fd);

			void newConnectionCb(int fd, const SocketAddress &peer);

			void newMessageCb(int fd, Buffer *buffer);

			Runner *runner_;
			Acceptor ls_;
			std::unique_ptr<Connection> connection_;
			NewMessageCb newMessageCb_;
			Map connections_;
	};


} /* namespace EchoServer */

#endif /* NEWEXAMPLES_SERVER_H_ */
