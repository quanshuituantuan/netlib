#ifndef THREADCPP_SRC_COMMON_LISTENINGSOCKET_H_
#define THREADCPP_SRC_COMMON_LISTENINGSOCKET_H_

#include <functional>

#include "SocketAddress.h"
#include "Socket.h"
#include "Context.h"

namespace EventLoop
{
    class Runner;
}

namespace EventLoop
{
    class Acceptor: public Context
    {
    public:
        typedef std::function <void (int fd, const SocketAddress &peerAddr)> NewConnectionCb;

        Acceptor(Runner *runner, const SocketAddress &socketAddr);

        ~Acceptor();

        void setNewConnectionCb(const NewConnectionCb &cb)
        {
            newConnectionCb_ = cb;
        }
        
    private:
        void handleInput() override;
        void handleOutput() override;
        void handleClose() override;
        void handleError() override;

        Runner  *runner_;
        SocketAddress sa_;
        Socket socket_;
        NewConnectionCb newConnectionCb_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_SRC_COMMON_LISTENINGSOCKET_H_ */
