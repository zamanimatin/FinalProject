#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "info.h"
#include "user.h"
class Customer : public User 
{
public:
    Customer(int _id,string _user_name,long unsigned int _password,string _email,int _age,int _money,
    vector<Film*> _bought_films,vector<User*> _followed_publishers);
    void add_a_publisher(User* p);
    vector<User*> get_followed_publishers(){return followed_publishers;}
    const string get_type(){return type;}
private:
    const string type = "Customer";
    
};
#endif