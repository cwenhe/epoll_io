#include "Connnection.h"
#include <errno.h>

#include <unistd.h>


namespace io
{


    Connection::Connection( NativeSocket const socket)
        :Socket(socket)
    {
    }


    Connection::~Connection()
    {

    }


    bool Connection::read( char* const buf, size_t len, size_t& read_len) const
    {
        size_t readed_size = 0;
        int read_count = 0;
        auto native_socket = this->getNativeSocket();
        while(read_count = ::read(native_socket, buf+readed_size, len - readed_size) > 0)
        {
            readed_size += read_count;
        }

        read_len = readed_size;

        return 0 != readed_size;
    }

    bool Connection::write( char const* const buf, size_t len) const
    {
        for(ssize_t left_len = len; left_len > 0; )
        {
            auto real_write_len = ::write(this->getNativeSocket(), buf + len - left_len, left_len);
            if(real_write_len < left_len)
            {
                //EAGAIN 已经没有要写入的数据
                if(-1 == real_write_len && EAGAIN != errno )
                {
                }
                break;

            }

            left_len -= real_write_len;
        }

        return true;
    }

    void Connection::read()
    {
        size_t read_len = 0;
        if(this->read(buf_.data(), buf_.size(), read_len))
        {
            if(data_processor_)
                data_processor_(buf_.data(), read_len);
        }
    }


} /* io */ 

