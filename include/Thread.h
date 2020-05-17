#ifndef THREADCPP_THREAD_H_
#define THREADCPP_THREAD_H_

#include <pthread.h>

#include <functional>

namespace EventLoop
{

    class Thread
    {
    public:
        friend void * threadFunction(void *args);
        typedef std::function<void ()> Function;

        Thread(Function &func);

        void start();

        void join();

        pthread_t getId() const;

        ~Thread();

    private:
        void stop();
        void execute();
        bool started_;
        bool joined_;
        pthread_attr_t attr_;
        pthread_t thread_;
        Function &func_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_THREAD_H_ */
