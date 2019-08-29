#include "detail/NetHostConversion.h"

#include <endian.h>


namespace detail
{
    uint64_t hton( uint64_t const host_value )
    {
        return htobe64(host_value);
    }

    uint32_t hton( uint32_t const host_value )
    {
        return htobe32(host_value);
    }

    uint16_t hton( uint16_t const host_value )
    {
        return htobe16(host_value);
    }

    uint64_t ntoh( uint64_t const net_value )
    {
        return be64toh(net_value);
    }

    uint32_t ntoh( uint32_t const net_value )
    {
        return be32toh(net_value);
    }

    uint16_t ntoh( uint16_t const net_value )
    {
        return be16toh(net_value);
    }
    
} /* io */ 
