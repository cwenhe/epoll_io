#pragma once

#include <arpa/inet.h>
#include <iostream>
#include <stdint.h>
#include <string>

#include "detail/IODef.h"

namespace detail 
{

    uint64_t hton( uint64_t const host_value );

    uint32_t hton( uint32_t const host_value );

    uint16_t hton( uint16_t const host_value );

    uint64_t ntoh( uint64_t const net_value );

    uint32_t ntoh( uint32_t const net_value );

    uint16_t ntoh( uint16_t const net_value );




    template<int _Protocol>
    bool pton(std::string const& src, typename ProtocolTraits<_Protocol>::AddrType& dst )
    {
        auto ret = ::inet_pton(ProtocolTraits<_Protocol>::protocol, src.c_str(), &dst);
        if(1 != ret)
        {
            std::cerr<<"inet_pton error"<<std::endl;
            return false;
        }
        return true;
    }


    template<int _Protocol>
    std::string ntop(typename ProtocolTraits<_Protocol>::AddrType const& dst)
    {
        using NetType = ProtocolTraits<_Protocol>;
        char buf[NetType::addr_str_len];
        auto ret = ::inet_ntop(NetType::protocol, &dst, buf, NetType::addr_str_len);
        if(nullptr != ret)
        {
            std::cerr<<"inet_pton error"<<std::endl;
        }

        return std::string(buf);
    }
    
} /* io */ 
