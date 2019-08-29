#pragma once

#include <stdint.h>

#include "detail/IODef.h"

namespace detail 
{

    void setnoblock(int fd);

    int epolladdevents(EpollId const epfd, int const fd, uint32_t const events );

    int epollmodevents(EpollId const epfd, int const fd, uint32_t const events );

    int epolldelevents(EpollId const epfd, int const fd, uint32_t const events );

    
} /* io */ 
