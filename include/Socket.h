#ifndef NETLIB_INCLUDE_SOCKET_H_
#define NETLIB_INCLUDE_SOCKET_H_
#include <sys/socket.h>

#include <exception>
#include <stdexcept>
#include <string>

#include "NoneCopyable.h"

namespace EventLoop
{
    class SocketAddress;
    class Buffer;
}

namespace EventLoop
{
    class SocketError: public std::runtime_error
    {
    public:
        SocketError(const std::string &msg):runtime_error(msg)
        {
        }

        ~SocketError()
        {
        }
    };

    class SocketSendPartDataError: public std::runtime_error
    {
    public:
        SocketSendPartDataError(const std::string &msg):runtime_error(msg)
        {
        }

        ~SocketSendPartDataError()
        {
        }
    };

    enum class How
    {
        DisableRead = ::SHUT_RD,
        DisableWrite = ::SHUT_WR,
        DiableReadWrite = ::SHUT_RDWR
    };

    class Socket: public NoneCopyable
    {
    public:
        Socket() = delete;

        explicit Socket(int fd);

        ~Socket();

        static int create(int domain, int type = SOCK_STREAM, int protocol = 0);

        void bind(const SocketAddress &sa);

        void listen();

        int accept(SocketAddress *peer);

        void connect(int fd, const SocketAddress &peer);

        int fd() { return fd_;}

        void setNoneBlock();

        void setReuseAddr(bool on);

        void send(Buffer *buffer);

        void send(const char *buffer, int len);

        void recv(Buffer *buffer);

        void recv(char *buffer, int len);

        void shutdown(const How &how);

        void closeFd();
    private:
        static int kMaxBacklogSize;
        int fd_;
    };

} /* namespace EventLoop */

#endif
