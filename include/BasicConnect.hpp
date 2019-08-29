#pragma once

#include <iostream>
#include <string.h>

#include "IConnectBase.h"
#include "NativeAddr.h"



namespace io
{

    template< typename _Type>
        class BasicConnect: public _Type, public IConnectBase
    {
        public:
            BasicConnect(NativeSocket const socket)
                :_Type(socket)
            {
            }


            bool connect( std::string const& ip, uint16_t port )
            {
                auto addr = NativeAddr::toAddr(ip, port);
                if(-1 == ::connect(this->getNativeSocket(), &addr, sizeof(addr)))
                {
                    std::cerr<<" connect error:"<<strerror(errno)<<std::endl;
                    return false;
                }

                return true;
            }
    };

}
