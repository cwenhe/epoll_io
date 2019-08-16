#pragma once

#include <atomic>
#include <unordered_map>
#include <thread>
#include <array>

#include "IODef.h"
#include "Loop.h"
#include "utility/Singleton.hpp"

struct epoll_event;

namespace io
{
    class BasicServer;
    class Connection;
    class EpollLoop: public Loop
    {
        public:
            virtual void run() override;

            virtual void post() override;

            bool addConnect( std::shared_ptr<Connection> connect);

            bool addServer( std::shared_ptr<BasicServer> server );

            virtual ~EpollLoop();


        protected:
            EpollLoop();


        private:
            void init_();

            void run_(bool detach );

            void workThread_();

            void handleEvents_( struct epoll_event* epoll_events, int count );

            void handleAccept_(std::shared_ptr<BasicServer> accept_server );


        private:
            std::unordered_map<NativeSocket, std::shared_ptr<BasicServer> > servers_;
            std::unordered_map<NativeSocket, std::shared_ptr<Connection> > connections_;

            std::thread work_thread_;
            std::atomic_bool stop_work_;

            EpollId epollid_;
    };

    using EpollLoopSingleton = utility::Singleton<EpollLoop>;
    
} /* io */ 
