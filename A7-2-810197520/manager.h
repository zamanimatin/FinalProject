#ifndef MANAGER_H
#define MANAGER_H
#include "info.h"
#include "film.h"
#include "user.h"
#include "publisher.h"
#include "customer.h"
#include <string>
class Manager
{
public:
    
    void add_a_film_to_data_base(Film* f);
    void add_a_publisher_to_data_base(Publisher* p);
    void add_a_customer_to_data_base(Customer* c);
    void change_a_film_data(int pub_id,int fil_id,string name
    ,string year,string length,string summary,string director);
    bool user_exists_with_name(string username);
    bool is_film_exists_in_publisher_list(Publisher* pub,Film* fil);
    MI change_central_info(MI& central_info,string data,int user_id,int new_system_sit);
    void set_client_data(int id,string username,int password,
    string email,int age,bool publisher_client_sit);
    void increase_system_salary(int film_price);
    void add_money_for_publisher_contribute(int publisher_id,int film_id);
    vector<Film*> get_data_base_all_films(){return data_base_all_films;}
    vector<Publisher*> get_data_base_all_publishers(){return data_base_all_publishers;}
    vector<Customer*> get_data_base_all_customers(){return data_base_all_customers;}
    bool get_publisher_sit(){return client_publisher_sit;}
    void set_data_base_info(vector<Film*> newfilms,vector<Publisher*> newpublishers,
    vector<Customer*> newcustomers);
    vector<User*> concat_user_vectors();
    User* find_user_with_id(int id);
    Film* find_film_with_id(int id);
    void show_unread_notices_for_user(string command);
    void show_read_notices_for_user(int limit);
    void show_user_purchased_films(string name,int price,int min_year,int max_year,string director);
    void comment_on_a_film_for_user(int film_id,string content);
    void rate_a_film_for_user(int film_id,float score);
    void buy_film_for_user(int film_id);
    bool is_film_exists(int film_id);
    void show_film_details_for_user(int film_id);
    vector<Film*> find_top_four_films(int film_id);
    Publisher*find_publisher_with_id(int publisher_id);
    vector<Film*> erase_film_with_id(int film_id,vector<Film*>&all_films);
    void process_user_search(string name, float min_rate,int min_year,int price,int max_year,string director);
    vector<Film*> make_all_filtered_films(string name,float mit_rate
    ,int min_year,int price,int max_year,string director);
    void show_all_filter_activated_films(vector<Film*>films);
    void show_recommends(int film_id);
    void reply_to_a_comment_for_publisher(int film_id,int comment_id,string content);
    void remove_a_comment_for_publisher(int film_id,int comment_id);
    void remove_a_film_for_publisher(int film_id);
    void increase_publisher_money(int amount,int publisher_id);
    void increase_user_money(int amount,MI central_info);
    void follow_a_publisher_for_a_customer(int publisher_id);
    void show_publisher_follow_list();
    void show_publisher_uploaded_films(string name,float min_rate,
    int min_year,int price,int max_year,string director);
    void show_publisher_films_all_filtered(string name,float min_rate,
    int min_year,int price,int max_year,string director);
    void show_publisher_films_semi_filtered(string name,float min_rate,
    int min_year,int price,int max_year,string director);
    void show_all_system_films();
    void show_publisher_all_films();
    vector<Film*> find_desired_films_with_name(string name,vector<Film*>desired);
    vector<Film*> find_desired_films_with_min_rate(float min_rate,vector<Film*>desired);
    vector<Film*> find_desired_films_with_min_year(int min_year,vector<Film*>desired);
    vector<Film*> find_desired_films_with_price(int price,vector<Film*>desired);
    vector<Film*> find_desired_films_with_max_year(int max_year,vector<Film*>desired);
    vector<Film*> find_desired_films_with_director(string director,vector<Film*>desired);
    int check_existence_error_throw(int count);
    vector<Film*> find_films_semi_filtered(string name,float min_rate,
    int min_year,int price,int max_year,string director,vector<Film*>films);
    void show_system_films_semi_filtered(string name,float min_rate,
    int min_year,int price,int max_year,string director);
    void get_publisher_his_share(int publisher_id);
    int get_client_id(){return client_id;}
    void set_data_base_film(vector<Film*>f){data_base_all_films=f;}
    void remove_film_from_all_with_id(int fid);
    void show_film_comments(int fid);
    bool is_publisher(string username);
    bool is_customer(string username);
    bool is_admin(string username);
    void login_admin(string username,long unsigned int password,MI& central_info);
    void login_publisher(string username,MI& central_info);
    void login_customer(string username,MI& central_info);
    void signup_publisher(string username,long unsigned int password,string email,int age,MI& central_info);
    void signup_customer(string username,long unsigned int password,string email,int age,MI& central_info);
    void show_get_money(MI central_info);
    map <int ,vector<int>> get_data_base_films_graph(){return data_base_films_graph;}
    void add_a_film_to_data_base_graph(Film*f);
    vector<int> find_common_customer_with_other_films(Film*f);
    void set_new_common_customers_for_film(int fid,vector<int> related_films);
    int calc_num_of_common_customers(Film* f1,Film* f2);
    void change_data_base_graph_for_this_film(int film_id);
    vector<int> find_common_customers_with_film_id(int film_id);
    int calc_num_of_vector_max_values(vector<int>v);
    bool is_film_exists_in_user_films(int user_id,int film_id);
protected:
    vector<Film*> data_base_all_films;
    vector<Publisher*> data_base_all_publishers;
    vector<Customer*> data_base_all_customers;
    int client_id;
    string client_username;
    int client_password;
    string client_email;
    string client_age;
    bool client_publisher_sit;
    int system_salary;
    map <int ,vector<int>> publishers_contribution;    
    map <int ,vector<int>> data_base_films_graph;
};
#endif