#include "detail/IOCtrl.h"

#include <fcntl.h>
#include <sys/epoll.h>

namespace detail
{

    static int epollctrlevents( EpollId const epfd, int const fd, int const op, uint32_t events)
    {
        struct epoll_event event;
        event.events = events;
        event.data.fd = fd;
        return ::epoll_ctl(epfd, op, fd, &event);
    }


    void setnoblock(int fd)
    {
        auto cur_flags = ::fcntl(fd, F_GETFL, 0);
        ::fcntl(fd, cur_flags|O_NONBLOCK);
    }


    int epolladdevents(EpollId const epfd, int const fd, uint32_t const events )
    {
        return epollctrlevents(epfd, fd, EPOLL_CTL_ADD, events);
    }


    int epollmodevents(EpollId const epfd, int const fd, uint32_t const events )
    {
        return epollctrlevents(epfd, fd, EPOLL_CTL_MOD, events);
    }

    
    int epolldelevents(EpollId const epfd, int const fd, uint32_t const events )
    {
        return epollctrlevents(epfd, fd, EPOLL_CTL_DEL, events);
    }
    

} /* utility */ 
