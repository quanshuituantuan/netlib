#include <functional>
#include <memory>

#include "TCPServer.h"

void newMessageCb(EventLoop::Connection *connection, EventLoop::Buffer *buffer)
{

    // int length = buffer->size();
    // std::cout<<"start new msg, length "<<length<<std::endl;;
    // std::cout<<"get message: "<<buffer->peek(&length)<<std::endl;
    connection->send(buffer);
    // std::cout<<"end new msg\n";
}


int main(int argc, char **argv)
{
    if(argc < 3)
    {
        std::cout<<"Usage: listener 127.0.0.1 5000"<<std::endl;
        return 0;
    }
    std::string ipv4(argv[1]);
    uint16_t port = atoi(argv[2]);

    std::cout<<"Ipv4: "<<ipv4<<std::endl;
    std::cout<<"newport: "<<port<<std::endl;
    EventLoop::SocketAddress sa(ipv4, port, false);
    EventLoop::EpollRunner runner;

    EventLoop::TCPServer  ss(&runner, sa);
    ss.setNewMessageCb(std::bind(&newMessageCb, std::placeholders::_1, std::placeholders::_2));
    runner.run();
    std::cout<<"endl run\n";
    return 0;
}





