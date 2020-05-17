#include "TCPClient.h"

void newConnectionCb(EventLoop::TCPClient &client)
{
    std::cout<<"start newConnectionCb\n";
    std::string s1(1023, 'a');
    std::string s2(1023, 'b');
    EventLoop::Buffer b1;
    EventLoop::Buffer b2;

    for(int i=0;i<1;i++)
    {
        std::cout<<"send out "<<i<<std::endl;
    // b1.append(s1);
    b2.append(s2);
    // client.send(&b1);
    client.send(&b2);
    }

    std::cout<<"end newConnectionCb\n";
}

void newMessageCb(EventLoop::Connection *, EventLoop::Buffer *buffer)
{
    std::cout<<"receive new msg\n";
    int length = buffer->size();
    char *s=buffer->retrive(&length);
    std::string s1(s, length);
    std::cout<<"length: "<<length<<" "<<s1<<std::endl;  
    std::cout<<"end receive new msg\n";

}
EventLoop::EpollRunner runner;
void handleInput(EventLoop::TCPClient &client)
{
    std::string s1(1024, 'a');
    std::string s2(1024, 'b');
    EventLoop::Buffer b1;
    EventLoop::Buffer b2;
    b1.append(s1);
    b2.append(s2);

    char c;
    std::cin>>c;
    if(c == 's')
    {
        std::cout<<"start to send\n";
        static int i=0;
        if(i%2 == 0)
        {
            client.send(&b1);
        }
        else 
        {
            client.send(&b2);
        }
        i++;
    }

    runner.addCallBack(std::bind(handleInput, std::ref(client)));
}


int main(int argc, char **argv) {

    if(argc < 3)
    {
        printf("usage: client 127.0.0.1 5000\n");
        return 0;
    }

    std::string ipv4(argv[1]);
    uint16_t port = atoi(argv[2]);

    EventLoop::SocketAddress sa(ipv4, port, false);
    
    EventLoop::TCPClient client(&runner, sa);
    client.setNewConnectionCb(std::bind(&newConnectionCb, std::ref(client)));
    client.setNewMessageCb(std::bind(newMessageCb, std::placeholders::_1, std::placeholders::_2));
    client.connect();
    // runner.addCallBack(std::bind(handleInput, std::ref(client)));

    try
    {
        runner.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    

    return 0;
}
