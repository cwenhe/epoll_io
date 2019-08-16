#include "BasicServer.h"

#include "Connnection.h"
#include "utility/NetHostConversion.h"
#include "utility/IOCtrl.h"

#include <arpa/inet.h>
#include <errno.h>
#include <iostream>
#include <string.h>
#include <sys/epoll.h>




namespace io
{

    BasicServer::BasicServer()
        :Socket(AF_INET, SOCK_STREAM, 0)
    {
    }


    BasicServer::~BasicServer()
    {
    }


    bool BasicServer::bind(std::string const& host, uint16_t const port)
    {
        struct sockaddr_in serv_addr;
        memset(&serv_addr, 0x00, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = hton(static_cast<decltype(serv_addr.sin_port)>(port));
        serv_addr.sin_addr.s_addr = inet_addr(host.c_str());

        if(-1 ==::bind(this->getNativeSocket(), (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
        {
            std::cerr<<"bind error:"<<strerror(errno)<<std::endl;
            return false;
        }

        return true;
    }


    bool BasicServer::listen( uint32_t backlog )
    {
        if(-1 == ::listen(this->getNativeSocket(), backlog))
        {
            std::cerr<<"listen error:"<<strerror(errno)<<std::endl;
            return false;
        }
        
        return true;
    }


    std::list<std::shared_ptr<Connection> > BasicServer::accept() const
    {
        struct sockaddr_in client_addr;
        socklen_t addr_len;

        std::list<std::shared_ptr<Connection> > connections;
        do
        {
            memset(&client_addr, 0x00, sizeof(client_addr));
            auto client_socket = ::accept(this->getNativeSocket(), (struct sockaddr*)(&client_addr), &addr_len);
            if(-1 == client_socket)
            {
                if(EAGAIN != errno)
                {
                    std::cerr<<"accept error:"<<strerror(errno)<<std::endl;
                }
                break;
            }

            connections.emplace_back(std::make_shared<Connection>(client_socket));

        }while(false);

        return connections;
    }

    
} /* io */ 

