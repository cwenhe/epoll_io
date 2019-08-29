#include "EpollLoop.h"

#include <cassert>
#include <errno.h>
#include <iostream>
#include <sys/epoll.h>
#include <string.h>

#include "BasicServer.h"
#include "Connnection.h"
#include "detail/IOCtrl.h"
#include "NativeAddr.h"


namespace io
{
    EpollLoop::EpollLoop()
    {
        this->init_();
    }


    EpollLoop::~EpollLoop()
    {
        if(work_thread_.joinable())
            work_thread_.join();
    }


    void EpollLoop::run()
    {
        this->run_(false);
    }


    void EpollLoop::post()
    {
        this->run_(true);
    }


    void EpollLoop::init_()
    {
        epollid_ = ::epoll_create(1);//argument is ignore but must more than zero
        if(-1 == epollid_)
        {
            std::cerr<<"epoll_create failed for "<<strerror(errno);
            assert(false);
        }
    }


    void EpollLoop::run_( bool detach )
    {
        std::thread work_thread(&EpollLoop::workThread_, this);
        if(detach)
            work_thread.detach();
        else
            work_thread.join();

        work_thread_ = std::move(work_thread);
    }


    void EpollLoop::workThread_()
    {

        static int MAX_EVENT_COUNT = 30;
        struct epoll_event epoll_events[MAX_EVENT_COUNT];
        while(!stop_work_)
        {
            auto events_count = ::epoll_wait(epollid_, epoll_events, MAX_EVENT_COUNT, -1);
            if(-1 == events_count)
            {
                std::cerr<<"epoll_wait error:"<< strerror(errno) <<std::endl;
                assert(false);
            }

            this->handleEvents_(epoll_events, events_count);
        }
    }


    bool EpollLoop::addConnect( std::shared_ptr<Connection> connect)
    {
        auto socket_id = connect->getNativeSocket();
        if(-1 == detail::epolladdevents(epollid_, socket_id, EPOLLIN|EPOLLET))
        {
            std::cerr<<" add event failed!"<<std::endl;
            return false;
        }

        connections_.emplace(socket_id, connect);
        return true;
    }


    bool EpollLoop::addServer( std::shared_ptr<BasicServer> server )
    {
        auto socket_id = server->getNativeSocket();
        if(-1 == detail::epolladdevents(epollid_, socket_id, EPOLLIN|EPOLLET))
        {
            std::cerr<<"server add events error for "<<strerror(errno)<<std::endl;
            return false;
        }

        servers_.emplace(socket_id, server);

        return true;
    }


    void EpollLoop::handleEvents_( struct epoll_event* epoll_events, int count )
    {
        for (int idx = 0; count != idx; ++idx)
        {
            auto epoll_event = epoll_events[idx];
            auto server_it = servers_.find(epoll_event.data.fd);
            if(servers_.end() != server_it)
                this->handleAccept_(server_it->second);
            else
            {
                auto connection_it = connections_.find(epoll_event.data.fd);
                if(connections_.end() == connection_it)
                {
                    std::cerr<<"connection["<<epoll_event.data.fd<<"]found"<<std::endl;
                    assert(false);
                }

                if(EPOLLIN & epoll_event.events)
                    connection_it->second->read();
                else if(EPOLLOUT & epoll_event.events)
                {
                }
            }
        }
    }

    void EpollLoop::handleAccept_(std::shared_ptr<BasicServer> accept_server )
    {
        auto connections= accept_server->accept();
        for (auto iter = connections.begin(); connections.end() != iter; ++iter)
        {
            auto& connection = *iter;
            //TODO need to set non block?
            if(-1 == detail::epolladdevents(epollid_, connection->getNativeSocket(), EPOLLIN|EPOLLET))
            {
                std::cerr<<"server add events error!"<<std::endl;
                break;
            }
            
            //TODO process connect notify?
            NativeAddr addr(connection->getNativeSocket());
            std::cout<<"client connet:"<<addr.addr()<<std::endl;

            this->addConnect(connection);
        }
    }

} /* io */ 
