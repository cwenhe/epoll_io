#include "NativeAddr.h"

#include <cassert>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <utility>

#include "utility/NetHostConversion.h"


namespace io
{

    NativeAddr::NativeAddr( NativeSocket const socket_id )
    {
        struct sockaddr addr;
        socklen_t sock_len;
        if(-1 == ::getsockname(socket_id, &addr, &sock_len))
        {
            std::cerr<<" getsockname error for "<<strerror(errno)<<std::endl;
            assert(false);
        }

        this->operator=(NativeAddr(&addr));
    }


    NativeAddr::NativeAddr(NativeAddr&& oth)
    {
        host_.swap(oth.host_);
        std::swap(port_, oth.port_);
    }


    NativeAddr& NativeAddr::operator=(NativeAddr&& oth)
    {
        if(&oth != this)
        {
            host_.swap(oth.host_);
            std::swap(port_, oth.port_);
        }
        return *this;
    }

    NativeAddr::NativeAddr( struct sockaddr const* addr)
        :NativeAddr(reinterpret_cast<struct sockaddr_in const*>(addr))
    {
    }

    NativeAddr::NativeAddr( struct sockaddr_in const* addr)
    {
        host_ = inet_ntoa(addr->sin_addr);
        port_ = io::ntoh(addr->sin_port);
    }



    struct sockaddr NativeAddr::toAddr() const
    {
        struct sockaddr_in addr;
        memset((char*)&addr, 0x00, sizeof(addr));
        addr.sin_addr.s_addr = inet_addr(host_.c_str());
        addr.sin_port = io::hton(static_cast<decltype(addr.sin_port)>(port_));

        return *reinterpret_cast<struct sockaddr*>(&addr);
    }

} /* io */ 

