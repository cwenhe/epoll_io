#include "NativeAddr.h"

#include <cassert>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <utility>

#include "detail/NetHostConversion.h"


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
        port_ = detail::ntoh(addr->sin_port);
    }



    struct sockaddr NativeAddr::toAddr() const
    {
        return NativeAddr::toAddr(host_, port_);
    }

    struct sockaddr NativeAddr::toAddr( std::string const& host, uint16_t const port)
    {
        struct sockaddr_in addr;
        memset((char*)&addr, 0x00, sizeof(addr));
        addr.sin_addr.s_addr = inet_addr(host.c_str());
        addr.sin_port = detail::hton(static_cast<decltype(addr.sin_port)>(port));

        return *reinterpret_cast<struct sockaddr*>(&addr);
    }

} /* io */ 

