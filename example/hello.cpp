#include <string>

#include "TCPClient.h"

std::string s("hello");
std::string r;

void newConnectionCb(EventLoop::TCPClient &client)
{
    EventLoop::Buffer b1;

    b1.append(s);
    std::cout<<"client to send"<<b1.size()<<std::endl;
    client.send(&b1);
}

bool c(true);
bool checkContinue()
{
    return c;
}

void newMessageCb(EventLoop::Connection *, EventLoop::Buffer *buffer)
{
    int length = buffer->size();
    char *s=buffer->retrive(&length);
    std::string s1(s, length);
    r = s1;
    std::cout<<"receive: "<<r<<std::endl;
    // conn->close();
    // c = false;
}




int main(int argc, char **argv) {

    if(argc < 3)
    {
        printf("usage: client 127.0.0.1 5000\n");
        return 0;
    }
    EventLoop::EpollRunner runner;

    std::string ipv4(argv[1]);
    uint16_t port = atoi(argv[2]);

    EventLoop::SocketAddress sa(ipv4, port, false);
    
    EventLoop::TCPClient client(&runner, sa);
    client.setNewConnectionCb(std::bind(&newConnectionCb, std::ref(client)));
    client.setNewMessageCb(std::bind(newMessageCb, std::placeholders::_1, std::placeholders::_2));
    client.connect();

    try
    {
        runner.run(checkContinue);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    if(s == r)
    {
        return 0;
    }
    else 
    {
        return -1;
    }
    
}
