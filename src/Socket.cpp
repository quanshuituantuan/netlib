#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <iostream>

#include "SocketAddress.h"
#include "Buffer.h"
#include "Socket.h"

namespace EventLoop
{
    int Socket::kMaxBacklogSize(1024);
    Socket::Socket(int fd):fd_(fd)
    {
    }

    Socket::~Socket()
    {
    	closeFd();
    }

    void Socket::closeFd()
    {
    	if(fd_ != -1)
    	{
    		::close(fd_);
    		fd_ = -1;
    	}
    }

    int Socket::create(int domain, int type, int protocol)
    {
        int fd = ::socket(domain, type, protocol);
        return fd;
    }

    void Socket::bind(const SocketAddress &sa)
    {
        int ret = ::bind(fd_, sa.getAddress(), sa.len());
        if(ret < 0)
        {
            throw SocketError("bind socket failed" + std::string(strerror(errno)));
        }
    }

    void Socket::listen()
    {
        /**
         *  accept queue size = min(backlog, /proc/sys/net/core/somaxconn)
         */
        int ret = ::listen(fd_, kMaxBacklogSize);
        if(ret < 0)
        {
            throw SocketError("listen to socket failed" + std::string(strerror(ret)));
        }
    }

    int Socket::accept(SocketAddress *peer)
    {
        int ret(0);
        do
        {
            struct sockaddr sa;
            int len = sizeof(sa);
            ret = ::accept(fd_, &sa, (socklen_t*)&len);
            peer->setAddress(sa);
        }while(ret == EINTR);

        if(ret < 0)
        {
            throw SocketError("accept error: " + std::string(strerror(errno)));
        }

        return ret;
    }

    void Socket::connect(int fd, const SocketAddress &peer)
    {
        int ret = 0;
        do
        {
            ret = ::connect(fd, peer.getAddress(), sizeof(struct sockaddr));
            if(ret < 0  && ret == EINTR)
            {
                throw SocketError("connect error: " + std::string(strerror(errno)));
            }
        }while(ret == EINTR);
    }

    void Socket::setNoneBlock()
    {
        int flag = ::fcntl(fd_, F_GETFL, 0);
        flag |= O_NONBLOCK;
        ::fcntl(fd_, F_SETFL, flag);

        flag = ::fcntl(fd_, F_GETFD, 0);
        flag |= FD_CLOEXEC;
        ::fcntl(fd_, F_SETFD, flag);
    }

    void Socket::setReuseAddr(bool on)
    {
        int optval = on ? 1 : 0;
        ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, static_cast<socklen_t>(sizeof optval));
    }

    void Socket::send(Buffer *buffer)
    {
    	int total = buffer->size();
        int length = total;
        // std::cout<<"send "<<length<<std::endl;
        // std::cout<<"start to send length: "<<length<<std::endl;

        /**
         * send only part of data is also error
         */
		int ret = ::send(fd_, buffer->peek(&length), length, 0);
        if(ret <0 && (ret == EAGAIN))
        {
            throw SocketSendPartDataError("sending buf full, try again later");
        }
		if(ret < 0 )
		{
			throw SocketError("send error: " + std::string(strerror(errno)));
		}
        if(ret > 0 && ret < total)
        {
            std::cout<<"send only part of data, total: "<<total<<" actual send: "<<ret;
            // throw SocketSendPartDataError(ss.str());
            // buffer->retrive(ret);
        }

        buffer->retrive(&ret);
        // std::cout<<"buf "<<buffer->size()<<std::endl;
    }

    void Socket::send(const char *buffer, int len)
    {
        int length = len;
        int ret = 0;
        do
        {
            ret = ::send(fd_, buffer, length, 0);
            if(ret < 0 && (ret != EINTR))
            {
                throw SocketError("send error: " + std::string(strerror(errno)));
            }
            if(ret == EINTR)
            {
                ret = 0;
            }
            length -= ret;
            buffer +=ret;
        }while(length > 0 || ret == EINTR);
    }

    void Socket::recv(Buffer *buffer)
    {
        char buf[1024];
        int len(1024);

        int ret = ::recv(fd_, buf, len, 0);
        /**
         * todo: error, need handle interupt case
         */
        if(ret < 0)
        {
            throw SocketError("receive error: " + std::string(strerror(errno)));
        }
//        ret = ::recv(fd_, buf, len, 0);
        if(ret == 0)
        {
            throw SocketError("peer socket already close");
        }
        //  std::cout<<"receive len: "<<ret<<std::endl;
        buffer->append(buf, ret);
        // std::cout<<"append data "<<std::endl;
    }

    void Socket::recv(char *buffer, int len)
    {
        int ret = ::recv(fd_, buffer, len, 0);
        if(ret < 0)
        {
            throw SocketError("receive error: " + std::string(strerror(errno)));
        }

        if(ret == 0)
        {
            std::cout<<"peer socket already close"<<std::endl;
            throw SocketError("peer socket already close");
        }
        std::cout<<"receive len: "<<len<<std::endl;
    }

    void Socket::shutdown(const How &how)
    {
        ::shutdown(fd_, static_cast<int>(how));
    }
} /* namespace EventLoop */


