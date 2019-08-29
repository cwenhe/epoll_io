#pragma once

#include <sys/socket.h>
#include <netinet/in.h>

using NativeSocket = int;
using EpollId = int;
using SocketType = int;
using SocketAddType = struct sockaddr;
using SocketIn4Type = struct sockaddr_in;
using In4AddrType = struct in_addr;
using SocketIn6Type = struct sockaddr_in6;
using In6AddrType = struct in6_addr;


static NativeSocket const INVALID_NATIVE_SOCKET = -1;

template<int>
struct ProtocolTraits
{
};

template<>
struct ProtocolTraits<AF_INET>
{
    using AddrType = In4AddrType;
    using SocketInType = SocketIn4Type;
    static const int protocol = AF_INET;
    static const int addr_str_len = INET_ADDRSTRLEN;
};

template<>
struct ProtocolTraits<AF_INET6>
{
    using AddrType = In6AddrType;
    using SocketInType = SocketIn6Type;
    static const int protocol = AF_INET6;
    static const int addr_str_len = INET6_ADDRSTRLEN;
};
