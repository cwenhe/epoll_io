#pragma once

#include <array>

#include "detail/AddressBase.h"
#include "detail/IODef.h"


namespace ip
{
    template<int _Protocol>
        class BasicAddress:public AddressBase
    {
        public:
            using AddrType = typename ProtocolTraits<_Protocol>::AddrType;
            using BytesType = std::array<char, sizeof(AddrType)>;

            explicit BasicAddress(AddrType const& addr );

            explicit BasicAddress( BytesType const& bytes );

            explicit BasicAddress( unsigned long addr );

            BasicAddress();

            std::shared_ptr<AddressBase> clone() const override;

            std::string toString() const override;

            bool isV4() const override;

            bool isV6() const override;

            char const* data() const override;

            size_t size() const override;

            static std::shared_ptr<AddressBase> fromString( std::string const& ip);


        private:
            AddrType addr_;

    };

    using AddressV4 = BasicAddress<AF_INET>;
    using AddressV6 = BasicAddress<AF_INET6>;
}


#include "detail/impl/BasicAddress.ipp"
