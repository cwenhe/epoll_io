#pragma once

#include <string>


namespace io
{
    class IConnectable
    {
        public:
            bool connect( std::string const& ip, uint16_t port );
    };


} /* io */ 
