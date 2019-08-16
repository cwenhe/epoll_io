#pragma once

#include <list>
#include <memory>
#include <string>

#include "Socket.h"


namespace io
{
    class Connection;
    class BasicServer: public Socket
    {
        public:
            BasicServer();

            ~BasicServer();

            virtual bool bind( std::string const& host, uint16_t const port );

            virtual bool listen( uint32_t backlog = 20);

            std::list<std::shared_ptr<Connection> > accept() const;

    };

    
} /*  io */ 
