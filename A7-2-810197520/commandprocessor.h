#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H
#include "info.h"
#include "manager.h"
#include "exceptions.h"
#include <iostream>
#include <string>
#include <regex>
using namespace std;
class CommandProcessor 
{
public:
    void set_manager(Manager* m){central_manager = m;}
    void general_process_command(MI& central_info);
    string remove_spaces(string line);
    string get_from_commandline();
    string get_first_command(string input);
    string get_second_command(string input);
    string return_query(string command);
    string return_type_of_command(string command);
    string put_mark_between_fields(string command);
    string get_desired_info(string query,string info);
    void make_add_new_user(string command,MI& central_info);
    bool check_user_sit(string query);
    long unsigned int hash_password(const char* password);
    bool signup_check(string command,MI central_info);
    bool is_valid_command(string command);
    bool is_valid_first_part(string command);
    bool is_valid_q_mark(string command);
    void run_entered_command(string command,MI& central_info,string query);
    void login_user(string command,MI& central_info);
    bool login_check(string command,MI central_info);
    bool add_film_check(string command,MI central_info);
    bool edit_film_check(string command,MI central_info);
    bool remove_film_check(string command,MI central_info);
    bool is_email_valid(const std::string& email);
    void add_film_for_a_publisher(string command,MI& central_info);
    void edit_a_film_data_for_a_publisher(string command,MI central_info);
    void process_show(string command,MI& central_info);
    bool process_show_check(string command,MI central_info);
    void process_get_films_command(string command,MI& central_info);
    bool check_process_get_films(string command,MI central_info);
    void process_delete_comments(string command,MI& central_info);
    bool check_comment_errors(string command, MI central_info);
    void process_reply(string command,MI& central_info);
    bool check_process_reply(string command,MI central_info);
    void process_delete_film(string command,MI& central_info);
    void process_post_money_command(string command,MI& central_info);
    bool check_post_money(string command,MI central_info);
    void process_follow_a_publisher(string command,MI& central_info);
    bool check_process_follow(string command,MI central_info);
    void process_show_publisher_follow_list(string command,MI& central_info);
    bool check_show_publisher_follow_list(string command,MI centra_info);
    void process_show_publisher_uploaded_films(string command,MI& central_info);
    bool check_show_publisher_uploaded_films(string command,MI central_info);
    bool consists_question_mark(string command);
    bool first_check(string command);
    void process_buy_command(string command,MI& central_info);
    bool check_process_buy(string command,MI central_info);
    void process_rate_command(string command,MI& central_info);
    bool check_process_rate(string command,MI central_info);
    void process_comment_on_a_film(string command,MI& central_info);
    bool check_process_comment_on_a_film(string command,MI central_info);
    void process_unread_notices(string command,MI& central_info);
    bool check_process_unread_notices(string command,MI central_info);
    void process_show_all_read_notices(string command,MI& central_info);
    bool check_show_all_read_notices(string command,MI central_info);
    bool first_command_check(string first_command,string command);
    void process_log_out(string command,MI& central_info);
    bool log_out_check(string command,MI central_info);
    void process_get_money(string command,MI& central_info);
    bool get_money_check(string command,MI central_info);
    void run_post_strings(string command,string command_type,MI& central_info);
    void run_get_strings(string command,string command_type,MI& central_info);
protected:
    Manager* central_manager;
};
#endif