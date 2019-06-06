#include "handlers.hpp"
#include "my_server.hpp"
#include <cstdlib> 
#include <ctime>  
#include <iostream>
#include "info.h"
#include "user.h"
#include "publisher.h"
#include "customer.h"
#include "manager.h"
#include "commandprocessor.h"
#include "exceptions.h"
using namespace std;
int main(int argc, char **argv) 
{
    MI central_info;
    while(central_info.system_sit!=SYSTEM_QUIT)
    {
        try {
        Manager* main_manager = new Manager();    
        CommandProcessor main_command_processor;
        CommandProcessor* commander = &main_command_processor;
        main_command_processor.set_manager(main_manager);
        MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
        server.setNotFoundErrPage("static/404.html");
        server.get("/signup",new ShowPage("static/signupcss.html"));
        server.post("/signup", new SignupHandler(main_manager,commander));
        server.get("/signupagain",new ShowPage("static/signupagaincss.html"));
        server.get("/login", new ShowPage("static/logincss.html"));
        server.post("/login", new LoginHandler(main_manager,commander));
        server.get("/loginagain",new ShowPage("static/loginagaincss.html"));
        server.get("/newfilm",new ShowPage("static/newfilmcss.html"));
        server.post("/newfilm",new NewFilmHandler(main_manager,commander));
        server.get("/userhome",new UserHandler(main_manager,commander));
        server.get("/profile",new ProfileHandler(main_manager,commander));
        server.post("/",new LogoutHandler(main_manager,commander));
        server.get("/home.png", new ShowImage("static/home.png"));
        server.get("/", new ShowPage("static/home.html"));
        server.run();
    } catch (exception& ex) {
        cerr << ex.what() << endl;
    }
  }
  return 0;
}
