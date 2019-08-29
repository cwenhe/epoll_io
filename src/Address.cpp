#include "Address.h"
#include "BasicAddress.h"


namespace ip
{

    Address::Address(ProtocolTraitsV4::AddrType const& addr)
    {
        address_ = std::make_shared<AddressV4>(addr);
    }


    Address::Address(ProtocolTraitsV6::AddrType const& addr)
    {
        address_ = std::make_shared<AddressV6>(addr);
    }


    Address::Address(std::string const& address)
        :AddressBase()
    {
        address_= AddressV4::fromString(address);
        if(!address_)
            address_ = AddressV6::fromString(address);

        assert(address_);
    }


    Address::Address(std::shared_ptr<AddressBase> const& address)
    {
        if(address)
            address_ = address->clone();
    }
    
    std::shared_ptr<AddressBase> Address::clone() const
    {
        auto cloned_address = std::make_shared<Address>(this->address_);
        return cloned_address;
    }


    std::string Address::toString() const
    {
        assert(address_);
        return address_->toString();
    }


    bool Address::isV4() const
    {
        assert(address_);
        return address_->isV4();
    }


    bool Address::isV6() const
    {
        assert(address_);
        return address_->isV6();
    }


    bool Address::isValid() const
    {
        return NULL != address_.get();
    }


    char const* Address::data() const
    {
        assert(address_);
        return address_->data();
    }


    size_t Address::size() const
    {
        assert(address_);
        return address_->size();
    }

} /* ip */ 
