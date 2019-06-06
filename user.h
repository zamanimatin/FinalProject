#ifndef USER_H
#define USER_H
#include <map>
#include <vector>
#include "info.h"
#include "film.h"
#include "exceptions.h"
class User 
{
public:
    User(int _id,string _user_name,long unsigned int _password,
    string _email,int _age,int _money,vector<Film*> _bought_films);
    void add_bought_film(Film* f);
    void increase_money(int m);
    void decrease_money(int m);
    void show_unreads();
    void show_reads(int limit);
    void show_all_films();
    void show_filtered_films(string name,int price,int min_year,int max_year,string director);
    void show_purchased_films(string name,int price,int min_year,int max_year,string director);
    bool does_have_film(int film_id);
    void add_an_unread_notice(string notice);
    void remove_from_unreads_add_to_reads(int notice_id);
    int get_last_unread_notice_id();
    int get_last_read_notice_id();
    int get_id(){return id;}
    string get_username(){return user_name;}
    int get_age(){return age;}
    long unsigned int get_password(){return password;}
    string get_email(){return email;}
    int get_money(){return money;}
    vector<Film*> get_bought_films(){return bought_films;}
    map <int, string> get_unread_notices(){return unread_notices;}
    map <int, string> get_read_notices(){return read_notices;}
    void add_a_publisher(User* p);
    vector<User*> get_followed_publishers(){return followed_publishers;}
    
protected:
    int id;
    string user_name;
    long unsigned int password;
    string email;
    int age;
    int money;
    vector<Film*> bought_films;
    vector<User*> followed_publishers;
    map <int, string> unread_notices;
    map <int, string> read_notices;
};
#endif