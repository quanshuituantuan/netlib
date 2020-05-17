#include <stdio.h>

#include "Thread.h"

namespace EventLoop
{

    void * threadFunction(void *args)
    {
        Thread *thread = static_cast<Thread *>(args);
        thread->execute();
        thread->stop();
        return NULL;
    }

    Thread::Thread(Function &func):
            started_(false),
            joined_(false),
            func_(func)
    {
        pthread_attr_init(&attr_);
        pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_JOINABLE);
    }

    void Thread::start()
    {
        pthread_create(&thread_, &attr_, threadFunction, this);
        started_ = true;
    }

    void Thread::join()
    {
        void *status;

        pthread_join(thread_, &status);

    }

    void Thread::stop()
    {
        pthread_exit(0);
    }

    pthread_t Thread::getId() const
    {
        return thread_;
    }

    void Thread::execute()
    {
        func_();
    }

    Thread::~Thread()
    {
        pthread_attr_destroy(&attr_);
    }

} /* namespace EventLoop */
