#include <stdint.h>
#include <strings.h>

#include <iostream>

#include <boost/lexical_cast.hpp>

#include "SocketAddress.h"

namespace EventLoop
{
    SocketAddress::SocketAddress()
    {
        ::bzero(&sa_, sizeof(sa_));
    }

    SocketAddress::SocketAddress(const std::string &address, uint16_t port, bool ipv6)
    {
    	if(ipv6)
    	{
    		sa_.in6.sin6_family = AF_INET6;
    		sa_.in6.sin6_port = htons(port);
			if(inet_pton(AF_INET6, address.c_str(), &sa_.in6.sin6_addr) <= 0)
			{
				std::cout<<"convert addresss error"<<std::endl;
			}
    	}
    	else
    	{
    		sa_.in.sin_family = AF_INET;
    		sa_.in.sin_port = htons(port);
			if(inet_pton(AF_INET, address.c_str(), &sa_.in.sin_addr) <= 0)
			{
				std::cout<<"convert addresss error"<<std::endl;
			}
    	}
    }

    const struct sockaddr *SocketAddress::getAddress() const
    {
        return &sa_.sa;
    }

    void SocketAddress::setAddress(const sockaddr &sa)
    {
    	sa_.sa = sa;
    }

    std::string SocketAddress::toString() const
    {
    	char address[INET6_ADDRSTRLEN];
    	int domain;
    	const char *sa(nullptr);
    	uint16_t port(0);

    	domain = sa_.sa.sa_family;
    	sa = (domain==AF_INET6)?reinterpret_cast<const char*>(&sa_.in6.sin6_addr): reinterpret_cast<const char*>(&sa_.in.sin_addr);
    	if(inet_ntop(domain, sa, address, INET6_ADDRSTRLEN) == nullptr)
		{
			std::cout<<"convert addresss error"<<std::endl;
		}

    	if(domain==AF_INET6)
    	{
    	    port = ntohs(sa_.in6.sin6_port);
    	}
    	else
    	{
    	    port = ntohs(sa_.in.sin_port);
    	}
    	return std::string(address) + ":" + boost::lexical_cast<std::string>(port);
    }

    SocketAddress::~SocketAddress()
    {
    }

} /* namespace EventLoop */
