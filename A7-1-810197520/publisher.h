#ifndef PUBLISHER_H
#define PUBLISHER_H
#include "info.h"
#include "user.h"
#include "exceptions.h"

class Publisher : public User
{
public:
    Publisher(int id,string user_name,long unsigned int password,string email,int age,int money,
    vector<Film*> bought_films,vector<Film*> uploaded_films,vector<User*> followers);
    void add_an_uploaded_film(Film* f);
    void add_a_follower(User* f);
    void set_uploaded_films(vector<Film*> v){uploaded_films = v;}
    void set_followers(vector<User*> f){followers = f;}
    void show_list_of_followers();
    void sort_followers_by_id();
    void delete_a_film_from_uploaded(int id);
    void edit_a_film(int film_id,string film_name,string film_year,
    string film_length,string film_summary,string film_director);
    void send_new_film_notice();
    void remove_a_film_with_id(int film_id);
    vector<Film*> get_uploaded_films(){return uploaded_films;} 
    vector<User*> get_followers(){return followers;}
    const string get_type(){return type;}
private:
    const string type = "Publisher";
    vector<Film*> uploaded_films;
    vector<User*> followers;
};
#endif