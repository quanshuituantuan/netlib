#ifndef NETLIB_INCLUDE_ACCEPTSOCKET_H_
#define NETLIB_INCLUDE_ACCEPTSOCKET_H_

#include <functional>

#include "Socket.h"
#include "Buffer.h"
#include "Context.h"

namespace EventLoop
{
    class Runner;
    class SocketAddress;
}

namespace EventLoop
{
    class Connection: public Context
    {
    public:
        typedef std::function<void (Buffer *buffer)> NewMessageCb;
        typedef std::function<void ()> MessageSendCb;
        typedef std::function<void (const std::string &error)> ErrorCb;
        typedef std::function<void ()> CloseCb;

        Connection(Runner *runner, int fd, const SocketAddress &peer);

        void send(Buffer *buffer);

        void setNewMessageCb(const NewMessageCb &cb)
        {
            newMessageCb_ = cb;
        }

        void setMessageSendCb(const MessageSendCb &cb)
        {
            messageSendCb_ = cb;
        }

        void setErrorCb(const ErrorCb &cb)
        {
            errorCb_ = cb;
        }

        void setCloseCb(const CloseCb &cb)
        {
        	closeCb_ = cb;
        }

        void close();

        virtual ~Connection();

    private:
        void handleInput() override;
         void handleOutput() override;
        void handleClose() override;
        void handleError() override;

    private:
        Runner *runner_;
        Socket socket_;
        NewMessageCb newMessageCb_;
        MessageSendCb messageSendCb_;
        CloseCb closeCb_;
        ErrorCb errorCb_;
        Buffer sendBuffer_;
        Buffer recvBuffer_;
        bool connectionClosed_;
    };

} /* namespace EventLoop */

#endif /* NETLIB_INCLUDE_ACCEPTSOCKET_H_ */
