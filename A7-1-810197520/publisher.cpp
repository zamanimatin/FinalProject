#include "publisher.h"

using namespace std;

Publisher::Publisher(int _id,string _user_name,long unsigned int _password,string _email,int _age,int _money,
vector<Film*> _bought_films,vector<Film*> _uploaded_films,vector<User*> _followers) : 
User(_id,_user_name,_password,_email,_age,_money,_bought_films)
{
    uploaded_films = _uploaded_films;
    followers = _followers;
}
void Publisher::add_an_uploaded_film(Film* f)
{
    uploaded_films.push_back(f);
}
void Publisher::add_a_follower(User* f)
{
    followers.push_back(f);
}
void Publisher::show_list_of_followers()
{
    this->sort_followers_by_id();
    cout<<"List of Followers"<<endl;
    cout<<"#. User Id | User Username | User Email"<<endl;
    for(int i=0;i<followers.size();i++)
    {
        cout<<i+1<<". "<<followers[i]->get_id()<<
        " | "<<followers[i]->get_username()<<" | "<<followers[i]->get_email()<<endl;
    }
}
void Publisher::remove_a_film_with_id(int film_id)
{
    for(int i=0;i<uploaded_films.size();i++)
    {
        if(uploaded_films[i]->get_id()==film_id)
        {
            uploaded_films.erase(uploaded_films.begin()+i);
        }
    }
    throw AccessError();
}
void Publisher::sort_followers_by_id()
{
    std::sort(followers.begin(), followers.end(), [](User* a, User* b){
        return a->get_id() < b->get_id();
    });
}
void Publisher::delete_a_film_from_uploaded(int id)
{
    for(int i=0;i<uploaded_films.size();i++)
        if(uploaded_films[i]->get_id() == id)
        {
            uploaded_films.erase(uploaded_films.begin()+ i);
            cout<<"OK"<<endl;
            return;
        }
    throw ExistenceError();
}
void Publisher::edit_a_film(int film_id,string film_name = 0,
string film_year = 0,string film_length = 0,string film_summary = 0,string film_director = 0)
{
    for(int i=0;i<uploaded_films.size();i++)
    {
        if(uploaded_films[i]->get_id() == film_id)
        {   
            uploaded_films[i]->change_film_info(film_name,film_year
            ,film_length,film_summary,film_director);
        }
    }
}
void Publisher::send_new_film_notice()
{
    for(int i=0;i<followers.size();i++)
    {
        followers[i]->add_an_unread_notice("Publisher "+ user_name +
        " with id " + to_string(id)+" register new film");
    }
}