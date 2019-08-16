#include "EpollLoop.h"
#include "EpollSever.h"

int main()
{
    std::shared_ptr<io::EpollSever> server(new io::EpollSever);
    server->bind("127.0.0.1", 1243);
    server->listen();
    server->setNonBlock();
    io::EpollLoopSingleton::instance().addServer(server);
    io::EpollLoopSingleton::instance().run();

    return 0;
}
