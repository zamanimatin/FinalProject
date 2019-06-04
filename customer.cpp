#include "customer.h"
Customer::Customer(int _id,string _user_name,long unsigned int _password,string _email,int _age,int _money,
vector<Film*> _bought_films,vector<User*> _followed_publishers) :
User(_id,_user_name,_password,_email,_age,_money,_bought_films)
{
    followed_publishers = _followed_publishers;
}
void Customer::increase_money(int m)
{
    money += m;
    int new_num = money;
    this->set_money(new_num);
}
void Customer::decrease_money(int m)
{
    money -= m;
}