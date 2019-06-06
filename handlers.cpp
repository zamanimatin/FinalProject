#include "handlers.hpp"

using namespace std;

SignupHandler::SignupHandler(Manager* m,CommandProcessor* c)
{
    manager = m;
    commander = c;
}
Response* SignupHandler::callback(Request* req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    string re_password = req->getBodyParam("re-password");
    string email = req->getBodyParam("email");
    int age = stoi(req->getBodyParam("age"));
    string sit = req->getBodyParam("publisher");
    bool publisher_sit = false;
    if(sit.size()!=0&&sit=="true")
        publisher_sit = true;
    long unsigned int hashed = commander->hash_password(password.c_str());
    if(!(manager->check_signup_params(username,password,re_password,email,to_string(age),sit,central_info)))
    {

        Response *res = Response::redirect("/signupagain");
        return res;
    }
    else
    {
        if(publisher_sit)
            manager->signup_publisher(username,hashed,email,age,central_info);
        else    
            manager->signup_customer(username,hashed,email,age,central_info);
    }
    Response* res = Response::redirect("/userhome");
    res->setHeader("username",username);
    res->setHeader("password",password);
    res->setHeader("email",email);
    res->setHeader("age",to_string(age));
    res->setHeader("publisher",sit);
    res->setSessionId(to_string(manager->get_client_id()));
    this->map_user_and_sessionId(UserIdSessionId,manager->get_client_id(),manager->get_client_id());
    return res;
}
LoginHandler::LoginHandler(Manager* m,CommandProcessor* c)
{
    manager = m;
    commander = c;
}
Response *LoginHandler::callback(Request *req) {
  string username = req->getBodyParam("username");
  string password = req->getBodyParam("password");
  long unsigned int hashed = commander->hash_password(password.c_str());
  req->setQueryParam("username",username,true);
  req->setQueryParam("password",to_string(hashed),true);
  req->setQueryParam("user_id",to_string(central_info.current_user_id),true);
  if(!(manager->check_login_params(username,password,hashed,central_info)))
  {
    Response *res = Response::redirect("/loginagain");
    return res;
  }
  else
  {
    cout << "username: " << username << ",\tpassword: " << password << endl;
    Response *res = Response::redirect("/userhome");
    Publisher* pub = manager->find_publisher_with_id(stoi(req->getSessionId()));
    Customer* cus = manager->find_customer_with_id(stoi(req->getSessionId()));
    if(pub!=NULL)
        manager->login_publisher(username,central_info);
    else if(cus!=NULL)
        manager->login_customer(username,central_info);
    res->setSessionId(to_string(manager->get_client_id()));
    res->setHeader("username",username);
    res->setHeader("password",to_string(hashed));
    res->setHeader("user_id",to_string(central_info.current_user_id));
    this->map_user_and_sessionId(UserIdSessionId,manager->get_client_id(),manager->get_client_id());
    return res;
  }
}
LogoutHandler::LogoutHandler(Manager* m, CommandProcessor*c)
{
    manager = m;
    commander = c;
}
Response* LogoutHandler::callback(Request* req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    Response* res = Response::redirect("/");
    res->setHeader("username",username);
    res->setHeader("password",password);
    res->setSessionId("");
    this->map_user_and_sessionId(UserIdSessionId,manager->get_client_id(),stoi(""));
    return res;
}
UserHandler::UserHandler(Manager* m,CommandProcessor* c)
{
    manager = m;
    commander = c;
}
Response* UserHandler::callback(Request* req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    Publisher* pub;
    Customer* cus;
    if(central_info.system_sit==PUBLISHER_ONLINE)
        pub = manager->find_publisher_with_id(manager->get_client_id());
    else if(central_info.system_sit==CUSTOMER_ONLINE)
        cus = manager->find_customer_with_id(manager->get_client_id());
    req->setQueryParam("username",username,true);
    req->setQueryParam("password",password,true);
    Response *res = new Response;
    res->setHeader("Content-Type", "text/html");
    string body;
    body = this->make_html_dynamic_code(pub);
    res->setSessionId(to_string(manager->get_client_id()));
    res->setHeader("username",username);
    res->setHeader("password",password);
    res->setBody(body);
    return res;
}
string UserHandler::make_html_dynamic_code(Publisher* pub)
{
    string body;
    body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<title> Home Page</title>";
    body += "<body style=\"text-align: left;color :red;\">";
    body += "<h1>Your Uploaded Films</h1>";
    body += "<br/><br/>";
    string film_info;
    body += "<p style=\"color:black;text-align:left;font-size:15 px;\">";
    if(pub!=NULL)
        for(int i=0;i<pub->get_uploaded_films().size();i++)
        {
            film_info = pub->get_uploaded_films()[i]->get_name()+
            to_string(pub->get_uploaded_films()[i]->get_price())+to_string(pub->get_uploaded_films()[i]->get_lenght())+
            to_string(pub->get_uploaded_films()[i]->get_rate())+to_string(pub->get_uploaded_films()[i]->get_year()) +
            pub->get_uploaded_films()[i]->get_director();
            body += film_info;
            body += "<form action =\"/userhome\" method=\"POST\">";
            body += "<button type=\"submit\" style=\" color:red; display: block;";
            body += "width:100px;height:40px;position:relative;left :10px;top : 0px;\">Remove</button>";
            body += "</form>";
        }
    body += "</p>";
    body += "<br/><br/>";
    body += "<form action=\"/\" method=\"POST\">";
    body += "<button type=\"submit\" style=\"color:red ; display: block;";
    body += "width:100px;height: 40px;position: relative; left:0px; top:10px;\">Logout</button>";
    body += "</form>";
    body += "<form action=\"/newfilm\" method=\"POST\">";
    body += "<button type=\"submit\" style=\"color: goldenrod;display:block;";
    body += "position:absolute;right:10px;top:50px;width: 120px;height: 40px;\"><em>NewFilm<em/></button>";
    body += "<form action=\"/profile\" method=\"POST\">";
    body += "<button type=\"submit\" style=\"color:green;display:block;";
    body += "position:absolute;right:10px;top:0px;width:120px;height: 40px;";
    body += "font-size: 17px;\"><em>Your Profile</em></button>";
    body += "</form>";
    body += "</body>";
    body += "</html>";
    return body;
}
ProfileHandler::ProfileHandler(Manager*m,CommandProcessor*c)
{
    manager = m;
    commander = c;
}
Response* ProfileHandler::callback(Request*req)
{
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
    string session_id = req->getSessionId();
    Response* res = new Response;
    User* user = manager->find_user_with_id(stoi(session_id));
    res->setHeader("Content-Type", "text/html");
    string body;
    body = this->make_html_dynamic_code(user);
    res->setBody(body);
    return res;
}
string ProfileHandler::make_html_dynamic_code(User*usr)
{
    string body;
    string film_info;
    body += body += "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<title>Your Profile</title>";
    body += "<body style=\"text-align: left;color :red;\">";
    body += "<h1>Your Bought Films</h1><br/><br/>";
    body += "<div><h3 style=\"color: black;position:absolute;";
    body += "right:10px;top:10px;font-size:15px;\">INCREASE YOUR MONEY HERE</h3>";
    body += "<input name=\"name\" type=\"number\" placeholder=\"How much do you wanna increase?\"";
    body += "style=\"display:block;margin:auto;margin-bottom:30px;padding:5px;width:250px;";
    body += "position: absolute;right:0px;top:50px;\"required/>";
    body += "<button type=\"submit\" style=\"color:blueviolet;display: block;";
    body += "width: 120px; height: 40px;position: absolute;top: 90px;right:0px;\">Add</button>";
    body += "</div>";
    for(int i=0;i<usr->get_bought_films().size();i++)
    {
        film_info = usr->get_bought_films()[i]->get_name()+
        to_string(usr->get_bought_films()[i]->get_price())+to_string(usr->get_bought_films()[i]->get_lenght())+
        to_string(usr->get_bought_films()[i]->get_rate())+to_string(usr->get_bought_films()[i]->get_year())+
        usr->get_bought_films()[i]->get_director();
        body += film_info;
    }
    body += "<form action=\"/profile\" method=\"POST\">";
    body += "<button type=\"submit\" style=\"color: red;display:block;";
    body += "width:120px;height: 40px;position: relative;left: 0px;top:10px;\">Logout</button>";
    body += "</form>";
    body += "<form action=\"/\" method=\"POST\">";
    body += "<button type=\"submit\" style=\"color:red ;display:block;";
    body += "width:100px;height: 40px;position: relative; left:0px; top:10px;\">Logout</button>";
    body += "</form>";
    body += "</body>";
    body += "</html>";
    return body;
}
NewFilmHandler::NewFilmHandler(Manager*m,CommandProcessor* c)
{
    manager = m; 
    commander = c;
}
Response* NewFilmHandler::callback(Request* req)
{   
    string name = req->getBodyParam("name");
    string director = req->getBodyParam("director");
    string length = req->getBodyParam("length");
    string year = req->getBodyParam("year");
    string price = req->getBodyParam("price");
    string rate = req->getBodyParam("rate");
    string summary = req->getBodyParam("summary");
    commander->add_film_for_a_publisher(name,year,length,price,summary,rate,director,central_info);
    Response* res = Response::redirect("/userhome");
    res->setHeader("name",name);
    res->setHeader("director",director);
    res->setHeader("length",length);
    res->setHeader("year",year);
    res->setHeader("price",price);
    res->setHeader("rate",rate);
    res->setHeader("summary",summary);
    return res;
}