#include "Socket.h"
#include "utility/IOCtrl.h"

#include <cassert>
#include <errno.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>


namespace io
{


    Socket::Socket(int const domain, int const type, int const protocol)
    {
        socket_ = ::socket(domain, type, protocol);
        if(INVALID_NATIVE_SOCKET == socket_)
        {
            std::cerr <<"init socket error:"<<strerror(errno)<<std::endl;
            assert(false);
        }
    }


    Socket::Socket()
        :Socket(INVALID_NATIVE_SOCKET)
    {
    }


    void Socket::init_()
    {
    }


    Socket::Socket( NativeSocket const socket )
    {
        this->setNativeSocket(socket);
    }


    void Socket::setNonBlock()
    {
        utility::setnoblock(socket_);
    }


    Socket::~Socket()
    {
        if(INVALID_NATIVE_SOCKET != this->socket_)
        {
            ::close(this->socket_);
        }

        this->socket_ = INVALID_NATIVE_SOCKET;
    }


    
} /* io */ 
