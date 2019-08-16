#pragma once


#include <functional>
#include <array>

#include "IStream.h"
#include "Socket.h"


namespace io
{

    typedef std::function< void( char const* const data, size_t len ) > DataProcessor;

    class Connection: public IStream, public Socket
    {
        public:
            Connection( NativeSocket const socket);

            virtual ~Connection();

            virtual bool read( char* const buf, size_t len, size_t& read_len) const override;

            virtual bool write( char const* const buf, size_t len) const override;

            void read();

            DataProcessor const& getDataProcessor()
            {
                return data_processor_;
            }

            void setDataProcessor( DataProcessor const& data_processor )
            {
                data_processor_ = data_processor;
            }


        private:
            DataProcessor data_processor_;
            std::array<char, 1024> buf_;

    };

    
} /* io */ 

