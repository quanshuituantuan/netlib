#include <unistd.h>

#include <iostream>
#include <functional>
#include <utility>
#include <exception>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

#include "../include/TCPServer.h"
#include "Thread.h"
#include "BlockQueue.h"
#include "ConsoleInput.h"
#include "Buffer.h"
#include "EpollRunner.h"
#include "Runner.h"

EventLoop::BlockQueue<std::pair<int, int>> block_queue(10);

void producer()
{
    while (1) {
        int dividend = rand()%10;
        int divisor = rand()%10;

        block_queue.put(std::make_pair(dividend, divisor));

        std::cout<<"produce: <"<<dividend<<", "<<divisor<<">"<<std::endl;
        sleep(1);
    }
}

void consumer()
{
    int count = 0;

    try {
        while (1) {
            std::pair<int, int> data(block_queue.get());
            if(data.second == 0) {
                throw std::runtime_error("zerro error");
            }
            double result  = data.first/data.second;
            count ++;

            result = result;
            std::cout<<"consume: <"<<data.first<<", "<<data.second<<">"<<std::endl;
            sleep(1);
        }
    }
    catch(std::exception &e) {
        std::cout<<"zero error happens"<<std::endl;
        std::cout<<"consumer: handle "<<count<<" data"<<std::endl;
    }
}

typedef std::function<void ()> Function;

void producerAndCosumer()
{
    Function producer_func = producer;
    Function consumer_func = consumer;

    EventLoop::Thread p(producer_func);
    EventLoop::Thread c(consumer_func);
    EventLoop::Thread c1(consumer_func);

    p.start();
    c.start();
    c1.start();

    p.join();
    c.join();
    c1.join();

}

//void socketServer(int ac, char **av)
//{
//    if(ac <= 1) {
//        std::cout<<"server ipv4:127.0.0.1:5000"<<std::endl;
//        return ;
//    }
//
//    bool can_continue(true);
//    EventLoop::EpollRunner runner(EventLoop::SignalSet(SIGINT),
//            [&can_continue](int sig)
//            {
//                if(sig == SIGINT) can_continue = false;
//            });
//
//    EventLoop::Server server(runner);
//    server.NewListeningSocket(boost::lexical_cast<EventLoop::SocketAddress>(av[1]));
//
//    runner.run([&can_continue]() { return can_continue;});
//
//    std::cout<<"done"<<std::endl;
//    return;
//}

void command(EventLoop::Buffer &buf)
{
    int size;

    size = 2;
    if(std::string("ls") == std::string(buf.peek(&size), 2)) {
        std::cout<<"Execute ls command"<<std::endl;
        buf.retrive(&size);
    }
    else if(std::string("pwd") == std::string(buf.peek(&(size=3)), 3)) {
        std::cout<<"Execute pwd command"<<std::endl;
        buf.retrive(&size);
    }
    else {
        std::cout<<"Not valid command"<<std::endl;
    }

}

void shell()
{
    EventLoop::EpollRunner runner;
    EventLoop::ConsoleInput input(runner, std::bind(&command, std::placeholders::_1));
    runner.run();
}

int main(int ac, char **av)
{
//    producerAndCosumer();
//    socketServer(ac, av);
//    shell();
    return 0;
}



