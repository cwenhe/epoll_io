#pragma once

#include "AddressBase.h"

namespace ip
{
    class Address: public AddressBase
    {

        public:
            Address(std::string const& address);

            Address(std::shared_ptr<AddressBase> const& address_);

            std::string toString() const override;

            bool isV4() const override;

            bool isV6() const override;

            char const* data() const override;

            size_t size() const override;

            std::shared_ptr<AddressBase> clone() const override;

            bool isValid() const;


        private:
            std::shared_ptr<AddressBase> address_;
    };


} /* ip */ 
