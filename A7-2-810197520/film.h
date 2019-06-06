#ifndef FILM_H
#define FILM_H
#include "info.h"
#include "exceptions.h"
class Film
{
public:
    Film(int publisher_id,string _name,int _id,float _rate,int _price,int _year,string _director,
    int _length,string _summary);
    void change_film_info(string film_name = 0,string film_year = 0,
    string film_length = 0,string film_summary = 0,string film_director = 0);
    void show_deteils();
    void show_comments();
    void show_responds(int comment_id);
    int get_film_situation();
    int calc_publisher_share();
    bool is_in_filter(string name,float min_rate);
    int find_commenter_id_with_comment_id(int comment_id);
    void delete_a_comment_with_id(int comment_id);
    void delete_a_comment_related_responds(int comment_id);
    void set_new_rate(float rate);
    void add_a_comment(int commenter_id,string content);
    void add_a_respond(int related_commenter_id,string respond);
    int get_last_comment_id();
    int get_last_respond_id();
    string make_summary_to_desired(string summary);
    void increase_raters(){num_rater++;}
    int get_publisher_id(){return publisher_id;}
    string get_name(){return name;}
    int get_id(){return id;}
    float get_rate(){return rate;}
    int get_price(){return price;}
    int get_year(){return year;}
    string get_director(){return director;}
    int get_lenght(){return length;}
    map <int ,map<int, string>>get_comments(){return comments;}
    map <int ,map<int, string>>get_responds(){return responds;}
private:
    int publisher_id;
    string name;
    int id;
    float rate;
    int num_rater;
    int price;
    int year;
    string director;
    int length;
    string summary;
    map <int ,map<int, string> >comments;
    map <int ,map<int, string> >responds;
};
#endif