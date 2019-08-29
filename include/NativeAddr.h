#pragma once

#include <string>
#include <cstdint>

#include <arpa/inet.h>

#include "detail/IODef.h"

namespace io
{

    class NativeAddr
    {
        public:
            explicit NativeAddr( NativeSocket const socket_id );

            explicit NativeAddr( struct sockaddr const* addr);

            explicit NativeAddr( struct sockaddr_in const* addr);

            NativeAddr(NativeAddr&& oth);

            NativeAddr& operator=(NativeAddr&& oth);

            std::string const& addr() const
            {
                return host_;
            }

            uint16_t port() const
            {
                return port_;
            }


            struct sockaddr toAddr() const;


            static struct sockaddr toAddr( std::string const& host, uint16_t const port );

        private:
            std::string host_;
            uint16_t port_;
    };
    
} /* io */ 
