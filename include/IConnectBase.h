#pragma once

#include <string>


namespace io
{
    class IConnectBase
    {
        public:
            bool connect( std::string const& ip, uint16_t port );
    };


} /* io */ 
