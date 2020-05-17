#ifndef INCLUDE_CONNECTOR_H_
#define INCLUDE_CONNECTOR_H_
#include <functional>

#include "Socket.h"
#include "SocketAddress.h"
#include "Buffer.h"
#include "Context.h"

namespace EventLoop
{
    class Runner;
}

namespace EventLoop
{

class Connector: public Context
{
public:
    typedef std::function <void (int fd, const SocketAddress &peerAddr)> ConnectionEstablishCb;

    Connector(Runner *runner, const SocketAddress &sa);

    void connect();
    
    void setConnectionEstablishCb(const ConnectionEstablishCb &cb);

    ~Connector();

private:
    void handleInput() override;
    void handleOutput() override;
    void handleClose() override;
    void handleError() override;

private:
    Runner *runner_;
    SocketAddress peer_;
    Socket socket_;
    bool connected_;
    ConnectionEstablishCb connectionEstablishCb_;
    Buffer input_;
};

} /* namespace EventLoop */

#endif /* INCLUDE_CONNECTOR_H_ */
