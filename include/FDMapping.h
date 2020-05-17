#ifndef THREADCPP_INCLUDE_COMMON_FDMAPPING_H_
#define THREADCPP_INCLUDE_COMMON_FDMAPPING_H_
#include <stdint.h>

#include <exception>
#include <map>
#include <utility>

#include "Context.h"

namespace EventLoop
{
    class FDMapping
    {
    public:
        class NoneExistFD: public std::runtime_error
        {
        public:
            explicit NoneExistFD(const std::string &s): runtime_error(s)
            {
            }
        };

        typedef std::pair<Context*, uint32_t> FDEvent;
        typedef std::map<int, FDEvent>  FDMap;

        FDMapping();

        FDMapping(const FDMapping &) = delete;

        FDMapping &operator = (const FDMapping &) = delete;

        void add(int fd, Context *fdlistener, uint32_t event);

        void modify(int fd, uint32_t event);

        void del(int fd);

        uint32_t getEvent(int fd);

        Context &getFDListener(int fd);

        int count();

        ~FDMapping();

    private:
        void checkFDExist(int fd);

        FDMap fdmap_;
    };

} /* namespace EventLoop */

#endif /* THREADCPP_INCLUDE_COMMON_FDMAPPING_H_ */
