#include "my_server.hpp"

MyServer::MyServer(int port) : Server(port) {}

void MyServer::set_manager(Manager* m,CommandProcessor* c)
{   
    manager = m;
    commander = c;
}
