#include <string>

#include "FDMapping.h"

namespace EventLoop
{
    FDMapping::FDMapping()
    {
    }

    void FDMapping::add(int fd, Context *fdlistener, uint32_t event)
    {
        FDEvent e(fdlistener, event);
        std::pair<FDMap::iterator, bool> ret(fdmap_.insert(std::make_pair(fd, e)));

        if(!ret.second) {
            fdmap_[fd].second |=event;
        }
    }

    void FDMapping::modify(int fd, uint32_t event)
    {
        auto i(fdmap_.find(fd));
        if(i == fdmap_.end()) {
            throw NoneExistFD("Modify none exist fd event");
        }

        fdmap_[fd].second = event;
    }

    void FDMapping::del(int fd)
    {
        FDMap::iterator iter = fdmap_.find(fd);
        if(iter != fdmap_.end()) {
            fdmap_.erase(iter);
        }
    }

    int FDMapping::count()
    {
        return fdmap_.size();
    }

    void FDMapping::checkFDExist(int fd)
    {
        auto iter = fdmap_.find(fd);
        if (iter == fdmap_.end())
        {
            throw NoneExistFD("FD not exist in FDMapping");
        }
    }

    uint32_t FDMapping::getEvent(int fd)
    {
        checkFDExist(fd);
        return fdmap_[fd].second;
    }

    Context &FDMapping::getFDListener(int fd)
    {
        checkFDExist(fd);
        return *(fdmap_[fd].first);
    }

    FDMapping::~FDMapping()
    {
    }

} /* namespace EventLoop */
