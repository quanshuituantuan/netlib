#ifndef THREADCPP_INCLUDE_COMMON_SOCKETADDRESS_H_
#define THREADCPP_INCLUDE_COMMON_SOCKETADDRESS_H_
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>

#include <string>

#include "Copyable.h"

namespace EventLoop
{
    class SocketAddress: public Copyable
    {
    public:
        SocketAddress();

        SocketAddress(const std::string &address, uint16_t port, bool ipv6);

        const struct sockaddr *getAddress() const;

        void setAddress(const struct sockaddr &sa);

        int family() { return sa_.sa.sa_family;}

        int len() const { return sizeof(sa_); }

        std::string toString() const;

        ~SocketAddress();

    protected:
        union SockAddr
        {
            struct sockaddr sa;
            struct sockaddr_in in;
            struct sockaddr_in6 in6;
        };

        SockAddr sa_;
    };
} /* namespace EventLoop */

#endif /* THREADCPP_INCLUDE_COMMON_SOCKETADDRESS_H_ */
