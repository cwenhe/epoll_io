#include <string.h>
#include <cassert>

#include "detail/NetHostConversion.h"


namespace ip
{

    template<int _Protocol>
        BasicAddress<_Protocol>::BasicAddress(AddrType const& addr )
            :addr_(addr)
        {
        }


    template<int _Protocol>
        BasicAddress<_Protocol>::BasicAddress()
        {
            memset(&addr_, 0x00, sizeof(addr_));//INADDR_ANY
        }


    template<int _Protocol>
        BasicAddress<_Protocol>::BasicAddress( BytesType const& bytes)
        {
            memcpy(&addr_, bytes.data(), sizeof(In4AddrType));
        }

    template<int _Protocol>
        BasicAddress<_Protocol>::BasicAddress( unsigned long addr )
        {
            addr_.s_addr = detail::hton(
                    static_cast<decltype(addr_.s_addr)>(addr));
        }


    template<int _Protocol>
        std::shared_ptr<AddressBase > BasicAddress<_Protocol>::fromString( std::string const& ip )
        {
            auto addr = std::make_shared<BasicAddress>();
            auto ret = detail::pton<_Protocol>(ip, addr->addr_);
            assert(ret);

            return addr;
        }


    template<int _Protocol>
        std::string BasicAddress<_Protocol>::toString() const
        {
            return detail::ntop<_Protocol>(this->addr_);
        }


    template<int _Protocol>
        char const* BasicAddress<_Protocol>::data() const
        {
            return reinterpret_cast<char const*>(&addr_);
        }


    template<int _Protocol>
        size_t BasicAddress<_Protocol>::size() const
        {
            return sizeof(addr_);
        }


    template<int _Protocol>
        std::shared_ptr<AddressBase> BasicAddress<_Protocol>::clone() const
        {
            std::shared_ptr<BasicAddress> cloned_address = std::make_shared<BasicAddress>();
            cloned_address->addr_ = addr_;

            return cloned_address;
        }


    template<int _Protocol>
        bool BasicAddress<_Protocol>::isV4() const
        {
            return AF_INET == _Protocol;
        }


    template<int _Protocol>
        bool BasicAddress<_Protocol>::isV6() const
        {
            return AF_INET6 == _Protocol;
        }


} /* ip */ 

