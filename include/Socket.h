#pragma once

#include <sys/types.h>
#include <sys/socket.h>

#include "detail/IODef.h"


namespace io
{
    class Socket
    {
        public:
            Socket();

            Socket(int const domain, int const type, int const protocol);

            explicit Socket(NativeSocket const socket);

            virtual ~Socket();

            NativeSocket const getNativeSocket() const
            {
                return socket_;
            }

            void setNativeSocket( NativeSocket const socket)
            {
                socket_ = socket;
            }

            void setNonBlock();


        private:
            void init_();


        private:
            NativeSocket socket_;
    };

}
