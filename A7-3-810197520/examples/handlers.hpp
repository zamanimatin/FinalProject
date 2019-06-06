#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include <cstdlib> 
#include <ctime>   
#include <iostream>
#include "manager.h"
#include "exceptions.h"
#include "commandprocessor.h"
#include "info.h"

class SignupHandler : public RequestHandler
{
public:
    SignupHandler(Manager*m,CommandProcessor* c);
    Response *callback(Request*);
protected:
    Manager* manager;
    CommandProcessor* commander;
};
class LoginHandler : public RequestHandler {
public:
    LoginHandler(Manager* m,CommandProcessor* c);
    Response *callback(Request *);
protected:
  Manager* manager;
  CommandProcessor* commander;
};
class UserHandler : public RequestHandler
{
public:
    UserHandler(Manager* m,CommandProcessor* c);
    Response *callback(Request*);
    string make_html_dynamic_code(Publisher*);
protected:
    Manager* manager;
    CommandProcessor* commander;
};
class ProfileHandler : public RequestHandler
{
public:
    ProfileHandler(Manager*m,CommandProcessor*c);
    Response *callback(Request*);
    string make_html_dynamic_code(User*);
protected:
    Manager* manager;
    CommandProcessor* commander;
};
class NewFilmHandler : public RequestHandler
{
public:
    NewFilmHandler(Manager*m,CommandProcessor* c);
    Response *callback(Request*);
private:
    Manager* manager;
    CommandProcessor* commander;
};
class LogoutHandler : public RequestHandler
{
public:
    LogoutHandler(Manager* m,CommandProcessor* c);
    Response *callback(Request*);    
protected:
    Manager* manager;
    CommandProcessor* commander;
};

#endif
