// #include <stdint.h>
// #include <string.h>
// #include <functional>

// #include "../include/Acceptor.h"
// #include "SocketAddress.h"
// #include "EpollRunner.h"

// using namespace EventLoop;

// void newConnectionCb(int fd, const SocketAddress &sa)
// {
//     std::cout<<"New connection come: fd="<<fd<<", address="<<sa.toString()<<std::endl;
// }

// int main(int argc, char **argv)
// {
//     if(argc < 3)
//     {
//         std::cout<<"Usage: listener 127.0.0.1 5000"<<std::endl;
//         return 0;
//     }

//     std::string ipv4(argv[1]);
//     uint16_t port = atoi(argv[2]);

//     SocketAddress sa(ipv4, port, false);

//     EpollRunner runner;
//     Acceptor ls(runner, sa);
//     ls.setNewConnectionCb(std::bind(newConnectionCb, std::placeholders::_1, std::placeholders::_2));
//     runner.run();

//     exit(0);
// }



