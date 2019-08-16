#pragma once

#include <stdint.h>

namespace io
{

    uint64_t hton( uint64_t const host_value );

    uint32_t hton( uint32_t const host_value );

    uint16_t hton( uint16_t const host_value );

    uint64_t ntoh( uint64_t const net_value );

    uint32_t ntoh( uint32_t const net_value );

    uint16_t ntoh( uint16_t const net_value );
    
} /* io */ 
