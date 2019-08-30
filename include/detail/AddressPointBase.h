#pragma once

#include "detail/IODef.h"

#include "Address.h"



namespace ip
{
    class AddressPointBase
    {
        public:
            virtual SocketAddType const* data() const = 0;

            virtual size_t size() const = 0;

            virtual uint16_t port() const = 0;

            virtual void port( uint16_t const port ) const = 0;

            virtual Address address() const = 0;

            virtual void address( Address const& address ) const = 0;

            virtual bool isV4() const = 0;

            virtual bool isV6() const = 0;

            virtual~ AddressPointBase()
            {
            }

    };
    
} /* ip */ 

