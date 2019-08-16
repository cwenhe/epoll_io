#pragma once

#include <sys/types.h>


namespace io
{
    class IStream
    {
        public:
            ~IStream()
            {
            }

            virtual bool read( char* const buf, size_t len, size_t& read_len) const = 0;

            virtual bool write( char const* const buf, size_t len) const = 0;

    };
    
} /* io */ 
