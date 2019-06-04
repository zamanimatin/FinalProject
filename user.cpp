#include "user.h"
User::User(int _id,string _user_name,long unsigned int _password,string _email,int _age,int _money,
vector<Film*> _bought_films)
{
    id = _id;
    user_name = _user_name;
    password = _password;
    email = _email;
    age = _age;
    money = _money;
    bought_films = _bought_films;
}
void User::show_unreads()
{
    cout<<"#. Notification Message"<<endl;
    for(std::map<int ,string>::iterator itr =unread_notices.begin();itr != unread_notices.end();++itr)
    {
        cout<<itr->first<<". "<<itr->second<<endl;
    }
}
void User::show_reads(int limit)
{
    cout<<"#. Notification Message"<<endl;
    auto iter = read_notices.rbegin();
    for(int i=0;i<limit&&iter!=read_notices.rend();i++)
    {
        cout<<i+1<<". "<<iter->second<<endl;
    }
}
void User::show_all_films()
{
    cout<<"#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director"<<endl;
    for(int i=0;i<bought_films.size();i++)
    {
        cout<<i+1<<" "<<bought_films[i]->get_id()<<" | ";
        cout<<bought_films[i]->get_name()<<" | ";
        cout<<bought_films[i]->get_lenght()<<" | ";
        cout<<bought_films[i]->get_price()<<" | ";
        cout<<bought_films[i]->get_rate()<<" | ";
        cout<<bought_films[i]->get_year()<<" | ";
        cout<<bought_films[i]->get_director()<<endl;
    }
}
void User::show_filtered_films(string name,int price,int min_year,int max_year,string director)
{
    cout<<"#. Film Id | Film Name | Film Length | Film Price | Rate | Production Year | Film Director"<<endl;
    for(int i=0;i<bought_films.size();i++)
    {
        if(bought_films[i]->get_name()==name&&bought_films[i]->get_price()==price&&
        bought_films[i]->get_director()==director&&
        bought_films[i]->get_year()>=min_year&&bought_films[i]->get_year()<=max_year)   
        {
            cout<<i+1<<" "<<bought_films[i]->get_id()<<" | ";
            cout<<bought_films[i]->get_name()<<" | ";
            cout<<bought_films[i]->get_lenght()<<" | ";
            cout<<bought_films[i]->get_price()<<" | ";
            cout<<bought_films[i]->get_rate()<<" | ";
            cout<<bought_films[i]->get_year()<<" | ";
            cout<<bought_films[i]->get_director()<<endl;
        }
    }
}
bool User::does_have_film(int film_id)
{
    for(int i=0;i<bought_films.size();i++)
        if(bought_films[i]->get_id()==film_id)
            return true;
    return false;
}
void User::show_purchased_films(string name,int price,
int min_year,int max_year,string director)
{
    if(name.size()==0&&price==0&&min_year==0&&max_year==0&&director.size()==0)
    {
        this->show_all_films();
    }
    else if(name.size()!=0||price!=0||min_year!=0||max_year!=0||director.size()!=0)
        this->show_filtered_films(name,price,min_year,max_year,director);
}
void User::add_bought_film(Film* f)
{
    bought_films.push_back(f);
}
void User::add_an_unread_notice(string notice)
{
    int id = this->get_last_unread_notice_id();
    id++;
    unread_notices.insert({id,notice});
}
int User::get_last_unread_notice_id()
{
    if(unread_notices.size()!=0)
        return unread_notices.rbegin()->first;
    else
        return ONE;
}
void User::remove_from_unreads_add_to_reads(int notice_id)
{
    auto node = unread_notices.find(notice_id);
    string content = node->second;
    int id = this->get_last_read_notice_id() ;
    id++;
    unread_notices.erase(notice_id);
    read_notices.insert({id ,content});
}
int User::get_last_read_notice_id()
{
    if(read_notices.size()!=0)
        return read_notices.rbegin()->first;
    else
        return ONE;
}
void User::add_a_publisher(User* p)
{
    followed_publishers.push_back(p);
    
}