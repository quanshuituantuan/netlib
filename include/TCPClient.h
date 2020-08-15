#ifndef INCLUDE_TCPCLIENT_H_
#define INCLUDE_TCPCLIENT_H_
#include <functional>
#include <memory>

#include "Acceptor.h"
#include "Connection.h"
#include "SocketAddress.h"
#include "Buffer.h"
#include "Runner.h"
#include "EpollRunner.h"
#include "Connector.h"

namespace EventLoop
{

    class TCPClient: public NoneCopyable
    {
    public:
        typedef std::function<void (void)> NewConnectionCb;
        typedef std::function<void (Connection* connection, Buffer *buffer)> NewMessageCb;
        TCPClient(Runner *runner, const SocketAddress &sa);

        ~TCPClient(){
            std::cout<<"destroy Client\n";
        }

        void connect();
        
        void send(Buffer *buffer);

        void close();
        
        void setNewConnectionCb(const NewConnectionCb &cb)
        {
            newConnectionCb_ = cb;
        }

        void setNewMessageCb(const NewMessageCb &cb)
        {
            newMessageCb_ = cb;
        }

    private:
        void newConnectionCb(int fd, const SocketAddress &peer);

        void newMessageCb(Buffer *buffer);

        void closeCB();

        Runner *runner_;
        Connector connector_;
        std::unique_ptr<Connection> connection_;
        NewConnectionCb newConnectionCb_;
        NewMessageCb newMessageCb_;
    };



} /* namespace EventLoop */

#endif /* INCLUDE_TCPCLIENT_H_ */
