#pragma once

#include <string>
#include <memory>

namespace ip
{
    class AddressBase
    {
        public:
            AddressBase()
            {}

            virtual ~AddressBase()
            { }

            virtual char const* data() const = 0;

            virtual size_t size() const = 0;

            virtual std::shared_ptr<AddressBase> clone() const = 0;

            virtual bool isV4() const = 0;

            virtual bool isV6() const = 0;

            virtual std::string toString() const = 0;


        private:
            AddressBase(AddressBase const& ) = delete;
            AddressBase(AddressBase && ) = delete;
            AddressBase& operator=(AddressBase const&) = delete;
            AddressBase& operator=(AddressBase &&) = delete;

    };

} /* ip */ 
