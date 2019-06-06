#ifndef __MY_SERVER__
#define __MY_SERVER__

#include "../server/server.hpp"
#include "manager.h"
#include "commandprocessor.h"
#include <map>
class MyServer : public Server {
public:
    MyServer(int port = 5000);
    void set_manager(Manager* m,CommandProcessor* c);
protected:
    Manager* manager;
    CommandProcessor* commander;
};

#endif
