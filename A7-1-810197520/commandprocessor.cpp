#include "commandprocessor.h"

string CommandProcessor::remove_spaces(string line)
{
    line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
    return line;  
}
void CommandProcessor::general_process_command(MI& central_info)
{
    string command;
    string query;
    command = this->get_from_commandline();
    command = this->put_mark_between_fields(command);
    query = this->return_query(command);
    this->run_entered_command(command,central_info,query);
}
string CommandProcessor::put_mark_between_fields(string query)
{
    for(int i=0;i<query.size();i++)
    {
        if(query[i]==' ' && query[i+1]== ' ')
            query.erase(i,ONE);
    }
    for(int i=0;i<query.size();i++)
    {
        if(query[i]== ' ')
            query[i] = LINE_MARK;
        else if(query[i]==LINE_MARK)
            query[i] = ' ';
    }
    query.append("|");
    return query;
}
string CommandProcessor::return_type_of_command(string command)
{
    string request = this->get_first_command(command);
    string type;
    for(int i=request.size();i<command.size();i++)
    {
        if(command[i]!=QUESTION_MARK)
            type += command[i];
        else if(command[i] == QUESTION_MARK)
            break;
    }
    return type;
}
string CommandProcessor::get_desired_info(string query,string info)
{
    string first_query = query;
    string name;
    string desired;
    int i=0;
    while(i != query.size()- 1&&query.size()!=0)
    {
        if(query[i]!= LINE_MARK)
            name += query[i];
        else if(name != info && query[i]==LINE_MARK)
        {
            name.clear();
        }
        else if(name == info)
        {
            query = query.substr(i);
            int j=1;
            while(query[j]!=LINE_MARK && j<query.size())
            {
                desired += query[j];
                j++;
            }
            if(desired != "password"&&desired!="age"&&desired != "email"&&
            desired != "publisher"&&desired!="name"&&desired!="username"&&
            desired!="content"&&desired!="film_id"&&desired != "price"&&
            desired!="min_year"&&desired!="max_year"&&desired!="director"&&
            desired!="score"&&desired!="min_rate"&&desired!="amount"&&
            desired!="user_id"&&desired!="comment_id"&&desired!="length"
            &&desired!="limit")
                return desired;
            else
            {
                return "";
            }
        }
        i++;
    }
    return "";
}
long unsigned int CommandProcessor::hash_password(const char* password)
{
    long unsigned int hash = 0;
    while (*password)
        hash = (hash * 10) + *password++ - '0';
    return hash;
}
bool CommandProcessor::consists_question_mark(string command)
{
    string first_command = this->get_first_command(command);
    string command_type = this->return_type_of_command(command);
    int size = first_command.size()+command_type.size();
    if(command[size]==QUESTION_MARK)
    {
        return true;
    }
    else
        return false;
}
string CommandProcessor::return_query(string command)
{
    int count = 0;
    if((this->consists_question_mark(command)))
    {
        for(int i=0;i<command.size();i++)
        {
            if(command[i]!=QUESTION_MARK)
                count++;
            else 
                break;
        }
        count++;
        command = command.substr(count);
        return command;
    }
    else 
        return "";
}
string CommandProcessor::get_from_commandline()
{   
    string input;
    while(input.length()==0)
        getline(cin,input);
    return input;
}
string CommandProcessor::get_first_command(string input)
{
    string in;
    for(int i=0;i<SIX;i++)
    {
        if(in == PUT_STRING || in == GET_STRING)
            break;
        else if(in == POST_STRING)
            break;
        else if(in == DELETE_STRING)
            break;
        in += input[i];
    }   
    return in;
}
string CommandProcessor::get_second_command(string input)
{
    string first = this->get_first_command(input);
    string second;
    for(int i=0;i<input.size();i++)
        while(input[i]!=QUESTION_MARK)
        {
            if(first == GET_STRING || first == PUT_STRING)
                second += input[i+THREE];
            else if(first == POST_STRING)
                second += input[i+FOUR];
            else if(first == DELETE_STRING)
                second += input[i+SIX];
        }
    return second;
}
bool CommandProcessor::is_valid_command(string command)
{
    command = this->remove_spaces(command);
    if(this->is_valid_first_part(command)&&this->is_valid_q_mark(command))
        return true;
    throw WrongRequest();
    return false;
}
bool CommandProcessor::is_valid_first_part(string command)
{
    int size;
    command.erase(command.begin()+SIX,command.end());
    size = command.size();
    switch(size)
    {
        case THREE:
            if(command == PUT_STRING || command == GET_STRING)
                return true;
        break;
        case FOUR:
            if(command == POST_STRING)
                return true;
        break;
        case SIX:
            if(command == DELETE_STRING)
                return true;
        break;
        default:
            return false;
            break;
    }
}
bool CommandProcessor::signup_check(string command)
{
    string query = this->return_query(command);
    string username = this->get_desired_info(query,"username");
    string password = this->get_desired_info(query,"password");
    string email = this->get_desired_info(query,"email");
    string age = this->get_desired_info(query,"age");
    if(username.size()==0||password.size()==0||email.size()==0||age.size()==0||query.size()==0)
    {
        return false;
    }
    for(int i=0;i<central_manager->concat_user_vectors().size();i++)
    {
        if(central_manager->concat_user_vectors()[i]->get_username() == username)
        {
            throw WrongRequest();
            return false;
        }
    }
    if(!(this->is_email_valid(email)))
    {
        throw WrongRequest();
        return false;
    }
    return true;
}   
bool CommandProcessor::is_valid_q_mark(string command)
{
    int size;
    command.erase(command.begin()+SEVEN,command.end());
    size = command.size();
    switch(size)
    {
        case FOUR:
            if(command[THREE]==QUESTION_MARK)
                return true;
        break;
        case FIVE:
            if(command[FOUR] == QUESTION_MARK)
                return true;
        break;
        case SEVEN:
            if(command[SIX] == QUESTION_MARK)
                return true;
        break;
        default:
        return false;
        break;
    }
}
void CommandProcessor::make_add_new_user(string command,MI& central_info)
{
    if(!(this->signup_check(command)))
    {
        throw WrongRequest();
        return ;
    }
    string query = this->return_query(command);
    string username = this->get_desired_info(query,"username");
    long unsigned int password = this->hash_password(this->get_desired_info(query,"password").c_str());
    bool sit = this->check_user_sit(query);
    if(sit==true)
    {
        vector<Film*> publisher_buy_film;
        vector<User*> publisher_followers;
        vector<Film*> publisher_sent_film;
        Publisher* newpub;
        newpub = new Publisher(central_info.central_client_id,username,password,
            this->get_desired_info(query,"email"),
            stoi(this->get_desired_info(query,"age")),ZERO,publisher_buy_film,
            publisher_sent_film,publisher_followers);
        central_manager->add_a_publisher_to_data_base(newpub);
        central_manager->set_client_data(central_info.central_client_id,username,
        password,this->get_desired_info(query,"email"),stoi(this->get_desired_info(query,"age")),true);
        central_info = central_manager->change_central_info(central_info,
        CENTRAL_CLIENT_ID,central_info.central_client_id,PUBLISHER_ONLINE);
        central_info = central_manager->change_central_info(central_info,
        SYSTEM_SIT,central_info.current_user_id,PUBLISHER_ONLINE);
        cout<<"OK"<<endl;
    }
    else if(sit == false)
    {
        vector<Film*> _bought_films;
        vector<User*> _followed_publishers;
        Customer* newcus = new Customer(central_info.central_client_id,username,
        password,this->get_desired_info(query,"email"),
        stoi(this->get_desired_info(query,"age")),ZERO,
        _bought_films,_followed_publishers);
        central_manager->add_a_customer_to_data_base(newcus);
        central_manager->set_client_data(central_info.central_client_id,
        username,password,this->get_desired_info(query,"email"),stoi(this->get_desired_info(query,"age")),false);
        central_info = central_manager->change_central_info(central_info,
        CENTRAL_CLIENT_ID,central_info.current_user_id,CUSTOMER_ONLINE);
        central_info = central_manager->change_central_info(central_info,
        SYSTEM_SIT,central_info.current_user_id,CUSTOMER_ONLINE);
        cout<<"OK"<<endl;
    }
}
bool CommandProcessor::check_user_sit(string query)
{
    string sit = this->get_desired_info(query,"publisher");
    if(sit.size()==0 || sit== "false")
    {
        return false;
    }
    else if(sit.size()!=0&&sit == "true")
        return true;
}
bool CommandProcessor::process_show_check(string command,MI central_info)
{
    if(central_info.system_sit==SYSTEM_QUIT||central_info.system_sit==NO_USER_ONLINE)   
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string name = this->get_desired_info(query,"name");
    string min_rate = this->get_desired_info(query,"min_rate");
    string min_year = this->get_desired_info(query,"min_year");
    string price = this->get_desired_info(query,"price");
    string max_year = this->get_desired_info(query,"max_year");
    string director = this->get_desired_info(query,"director");
    if(query.size()!=0&&name.size()==0&&min_rate.size()==0&&
    min_year.size()==0&&price.size()==0&&max_year.size()==0&&director.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::process_show(string command,MI& central_info)
{
    if(!(this->process_show_check(command,central_info)))
        return;
    string query = this->return_query(command);
    string name = this->get_desired_info(query,"name");
    int price,min_year,max_year;
    string director;
    if(this->get_desired_info(query,"price").size()!=0)
        price = stoi(this->get_desired_info(query,"price"));
    else
        price = 0;
    if(this->get_desired_info(query,"min_year").size()!=0)
        min_year = stoi(this->get_desired_info(query,"min_year"));
    else
        min_year = 0;
    if(this->get_desired_info(query,"max_year").size()!=0)
        max_year = stoi(this->get_desired_info(query,"max_year"));
    else
        max_year = 0;
    if(this->get_desired_info(query,"director").size()!=0)
        director = this->get_desired_info(query,"director");
    central_manager->show_user_purchased_films(name,price,min_year,max_year,director);
}
bool CommandProcessor::first_command_check(string first_command,string command)
{
    if(first_command!=POST_STRING||first_command!=PUT_STRING
    ||first_command!=GET_STRING||first_command!=DELETE_STRING)
    {
        throw WrongRequest();
        return false;   
    }
    return true;
}
void CommandProcessor::run_entered_command(string command,MI& central_info,string query)
{
    string first_command = this->get_first_command(command);
    string command_type = this->return_type_of_command(command);
    if(first_command==POST_STRING && command_type =="|signup|"&&central_info.system_sit!=SYSTEM_QUIT)
    {
        try
        {
            this->make_add_new_user(command,central_info);
            
        }catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }
    else if(first_command==POST_STRING && command_type=="|login|"&&central_info.system_sit!=SYSTEM_QUIT)
    {
        try
        {
            this->login_user(command,central_info);    
        }catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }
    else if(first_command==POST_STRING&& command_type == "|films|")
    {
        try
        {
            this->add_film_for_a_publisher(command,central_info);      
        }catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }
    else if(first_command==PUT_STRING&&command_type =="|films|")
    {
        try
        {
            this->edit_a_film_data_for_a_publisher(command,central_info);
        }catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }
    else if(first_command==DELETE_STRING&&command_type=="|films|")
    {
        try
        {
            this->process_delete_film(command,central_info);
        }catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }
    else if(first_command==POST_STRING&&command_type=="|followers|")
    {
        try
        {
            this->process_follow_a_publisher(command,central_info);
        }catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }
    else if(first_command==GET_STRING&&command_type=="|followers|")
    {
        try
        {
            this->process_show_publisher_follow_list(command,central_info);
        }catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }
    else if(first_command==POST_STRING&&command_type=="|money|")
    {
        try
        {
            this->process_post_money_command(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }       
    }
    else if(first_command==GET_STRING&&command_type=="|published|")
    {
        try
        {
            this->process_show_publisher_uploaded_films(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }   
    }
    else if(first_command==POST_STRING&&command_type=="|replies|")
    {
        try
        {
            this->process_reply(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }     
    }
    else if(first_command==DELETE_STRING&&command_type=="|comments|")
    {
        try
        {
            this->process_delete_comments(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }     
    }
    else if(first_command==GET_STRING&&command_type=="|films|")
    {
        try
        {
            this->process_get_films_command(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }     
    }
    else if(first_command==POST_STRING&&command_type=="|buy|")
    {
        try
        {
            this->process_buy_command(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }     
    }
    else if(first_command==POST_STRING&&command_type=="|rate|")
    {
        try
        {
            this->process_rate_command(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }     
    }
    else if(first_command==POST_STRING&&command_type=="|comments|")
    {
        try
        {
            this->process_comment_on_a_film(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }     
    }
    else if(first_command==GET_STRING&&command_type=="|purchased|")
    {
        try
        {
            this->process_show(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }     
    }
    else if(first_command==GET_STRING&&command_type=="|notifications|")
    {
        try
        {
            this->process_unread_notices(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }     
    }
    else if(first_command==GET_STRING&&command_type=="|notifications|read|")
    {
        try
        {
           this->process_show_all_read_notices(command,central_info);
        }
        catch(exception& ex)
        {
            cout<<ex.what()<<endl;
        }
    }
    else
    {
        try
        {
            this->first_command_check(first_command,command);
        }
        catch(exception& ex){
            cout<<ex.what()<<endl;
        }
    }
    
}
bool CommandProcessor::check_show_all_read_notices(string command,MI central_info)
{
    if(central_info.system_sit==SYSTEM_QUIT||central_info.system_sit==NO_USER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string limit = this->get_desired_info(query,"limit");
    if(query.size()==0||limit.size()==0)
    {
        throw WrongRequest();
        return false;
    }
}
void CommandProcessor::process_show_all_read_notices(string command,MI& central_info)
{   
    if(!(this->check_show_all_read_notices(command,central_info)))
        return;
    int limit = stoi(this->get_desired_info(this->return_query(command),"limit"));
    central_manager->show_read_notices_for_user(limit);
}
bool CommandProcessor::check_process_unread_notices(string command,MI central_info)
{
    if(central_info.system_sit==SYSTEM_QUIT||central_info.system_sit==NO_USER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    if(query.size()!=0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::process_unread_notices(string command,MI& central_info)
{
    if(!(this->check_process_unread_notices(command,central_info)))
        return ;
    central_manager->show_unread_notices_for_user(command);   
}
bool CommandProcessor::check_process_comment_on_a_film(string command,MI central_info)
{
    if(central_info.system_sit==SYSTEM_QUIT||central_info.system_sit==NO_USER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string film_id = this->get_desired_info(query,"film_id");
    string content = this->get_desired_info(query,"content");
    if(query.size()==0||film_id.size()==0||content.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    int fid = stoi(this->get_desired_info(query,"film_id"));
    Film* des = central_manager->find_film_with_id(fid);
    User* usr = central_manager->find_user_with_id(central_manager->get_client_id());
    for(int i=0;i<usr->get_bought_films().size();i++)
    {
        if(des->get_id()==usr->get_bought_films()[i]->get_id())
        {
            return true;   
        }
        else if(des->get_id()==usr->get_bought_films()[i]->get_id()&&i==usr->get_bought_films().size()-ONE)
        {
            throw ExistenceError();
            return false;
        }
    }
}
void CommandProcessor::process_comment_on_a_film(string command,MI& central_info)
{
    if(!(this->check_process_comment_on_a_film(command,central_info)))
        return ;
    string query = this->return_query(command);
    string content = this->get_desired_info(query,"content");
    int film_id = stoi(this->get_desired_info(query,"film_id"));
    central_manager->comment_on_a_film_for_user(film_id,content);
} 
bool CommandProcessor::check_process_rate(string command,MI central_info)
{
    if(central_info.system_sit==SYSTEM_QUIT||central_info.system_sit==NO_USER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string film_id = this->get_desired_info(query,"film_id");
    string score = this->get_desired_info(query,"score");
    if(query.size()==0||film_id.size()==0||score.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    int fid = stoi(this->get_desired_info(query,"film_id"));
    int scr = stoi(this->get_desired_info(query,"score"));
    if(scr<ONE||scr>TEN)
    {
        throw WrongRequest();
        return false;
    }
    Film* des = central_manager->find_film_with_id(fid);
    if(!(central_manager->is_film_exists(fid)))
    {
        throw ExistenceError();
        return false;
    }
    return true;
}
void CommandProcessor::process_rate_command(string command,MI& central_info)
{
    
    if(!(this->check_process_rate(command,central_info)))
        return ;
    string query = this->return_query(command);
    int film_id = stoi(this->get_desired_info(query,"film_id"));
    float score = stof(this->get_desired_info(query,"score"));
    central_manager->rate_a_film_for_user(film_id,score);
}
bool CommandProcessor::check_process_buy(string command,MI central_info)
{
    if(central_info.system_sit==SYSTEM_QUIT||central_info.system_sit==NO_USER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string film_id = this->get_desired_info(query,"film_id");
    User* client = central_manager->find_user_with_id(central_manager->get_client_id());
    if(query.size()==0||film_id.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    int fid = stoi(this->get_desired_info(query,"film_id"));
    for(int i=0;i<central_manager->get_data_base_all_films().size();i++)
    {
        if(central_manager->get_data_base_all_films()[i]->get_id()==fid)
        {
            if(client->get_money()<central_manager->get_data_base_all_films()[i]->get_price())
            {
                throw AccessError();
                return false;
            }
            return true;
        }
        else if(central_manager->get_data_base_all_films()[i]->get_id()==fid&&
        i==central_manager->get_data_base_all_films().size()-1)
        {
            throw ExistenceError();
            return false;
        }
    }
}
void CommandProcessor::process_buy_command(string command,MI& central_info)
{
    if(!(this->check_process_buy(command,central_info)))
        return ;
    string query = this->return_query(command);
    int film_id = stoi(this->get_desired_info(query,"film_id"));
    central_manager->buy_film_for_user(film_id);
    cout<<"OK"<<endl;
}
bool CommandProcessor::check_show_publisher_uploaded_films(string command,MI central_info)
{
    if(central_info.system_sit!=PUBLISHER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    
    string name = this->get_desired_info(query,"name");
    string min_rate = this->get_desired_info(query,"min_rate");
    string min_year = this->get_desired_info(query,"min_year");
    string price = this->get_desired_info(query,"price");
    string max_year = this->get_desired_info(query,"max_year");
    string director = this->get_desired_info(query,"director");
    if(query.size()!=0&&name.size()==0&&min_rate.size()==0&&
    min_year.size()==0&&price.size()==0&&max_year.size()==0&&director.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::process_show_publisher_uploaded_films(string command,MI& central_info)
{
    if(!(this->check_show_publisher_uploaded_films(command,central_info)))
        return ;
    string query = this->return_query(command);
    string name,director;
    int min_year=0,price=0,max_year=0;
    float min_rate=0;
    name = this->get_desired_info(query,"name");
    director = this->get_desired_info(query,"director");
    if(this->get_desired_info(query,"min_rate").size()!=0)
        min_rate = stof(this->get_desired_info(query,"min_rate"));
    if(this->get_desired_info(query,"min_year").size()!=0)
        min_year = stoi(this->get_desired_info(query,"min_year"));
    if(this->get_desired_info(query,"price").size()!=0)
        price = stoi(this->get_desired_info(query,"price"));
    if(this->get_desired_info(query,"max_year").size()!=0)
        max_year = stoi(this->get_desired_info(query,"max_year"));

    central_manager->show_publisher_uploaded_films(name,min_rate,min_year,price,max_year,director);
}
bool CommandProcessor::check_show_publisher_follow_list(string command,MI centra_info)
{
    string query = this->return_query(command);
    if(centra_info.system_sit!=PUBLISHER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    if(query.size()!=0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::process_show_publisher_follow_list(string command,MI& central_info)
{
    if(!(this->check_show_publisher_follow_list(command,central_info)))
        return;
    central_manager->show_publisher_follow_list();   
}
bool CommandProcessor::check_process_follow(string command,MI central_info)
{
    if(central_info.system_sit==SYSTEM_QUIT||central_info.system_sit==NO_USER_ONLINE)
    {

        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string user_id = this->get_desired_info(query,"user_id");
    if(query.size()==0||user_id.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    int uid = stoi(this->get_desired_info(query,"user_id"));
    for(int i=0;i<central_manager->get_data_base_all_publishers().size();i++)
    {
        if(central_manager->get_data_base_all_publishers()[i]->get_id()==uid)
            return true;
    }
    throw ExistenceError();
    return false;
}
void CommandProcessor::process_follow_a_publisher(string command,MI& central_info)
{
    if(!(this->check_process_follow(command,central_info)))
        return ;
    string query = this->return_query(command);
    int user_id ;
    if(this->get_desired_info(query,"user_id").size()!=0)
    {
        user_id = stoi(this->get_desired_info(query,"user_id"));
        central_manager->follow_a_publisher_for_a_customer(user_id);
        cout<<"OK"<<endl;
    }
}
bool CommandProcessor::check_post_money(string command,MI central_info)
{
    string query = this->return_query(command);
    if(central_info.system_sit==NO_USER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    if(query.size()!=0&&this->get_desired_info(query,"amount").size()==0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::process_post_money_command(string command,MI& central_info)
{
    if(!(this->check_post_money(command,central_info)))
    {
        return;
    }
    string query = this->return_query(command);
    int amount = stoi(this->get_desired_info(query,"amount"));
    if(query.size()==0&&central_info.system_sit==PUBLISHER_ONLINE)
        central_manager->get_publisher_his_share(central_manager->get_client_id());
    if(query.size()!=0&&(central_info.system_sit==CUSTOMER_ONLINE||
    central_info.system_sit==PUBLISHER_ONLINE))
        central_manager->increase_user_money(amount,central_info);
}
bool CommandProcessor::remove_film_check(string command,MI central_info)
{
    if(central_info.system_sit!=PUBLISHER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string film_id = this->get_desired_info(query,"film_id");
    if(query.size()==0||film_id.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    int fid = stoi(film_id);
    for(int i=0;i<central_manager->get_data_base_all_films().size();i++)
    {
        if(central_manager->get_data_base_all_films()[i]->get_id()==fid)
        {
            return true;
        }
    }
    throw ExistenceError();
    return false;
}
void CommandProcessor::process_delete_film(string command,MI& central_info)
{
    if(!(this->remove_film_check(command,central_info)))
    {
        return;
    }
    string query = this->return_query(command);
    int film_id;
    if(this->get_desired_info(query,"film_id").size()!=0)
    {
        film_id = stoi(this->get_desired_info(query,"film_id"));
        central_manager->remove_a_film_for_publisher(film_id);
    }
    cout<<"OK"<<endl;
}
bool CommandProcessor::check_comment_errors(string command, MI central_info)
{
    if(central_info.system_sit!=PUBLISHER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string film_id = this->get_desired_info(query,"film_id");
    string comment_id = this->get_desired_info(query,"comment_id");
    if(query.size()==0||film_id.size()==0||comment_id.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    int fid = stoi(this->get_desired_info(query,"film_id"));
    int cid = stoi(this->get_desired_info(query,"comment_id"));
    Publisher* pub = central_manager->find_publisher_with_id(central_manager->get_client_id());
    if(central_manager->is_film_exists(fid))
    {
        throw ExistenceError();
        return false;
    }
    for(int i=0;i<pub->get_uploaded_films().size();i++)
    {
        if(pub->get_uploaded_films()[i]->get_id() == fid)
        {
            Film* film = pub->get_uploaded_films()[i];
            for(auto iter = film->get_comments().begin();iter!=film->get_comments().end();iter++)
            {
                if(iter->first == cid)
                    return true;
            }
            throw ExistenceError();
            return false;
        }
        else if(pub->get_uploaded_films()[i]->get_id()!=fid&&i==pub->get_uploaded_films().size()-1)
        {
            throw AccessError();
            return false;    
        }
    } 
}
bool CommandProcessor::check_process_reply(string command,MI central_info)
{
    string query = this->return_query(command);
    string content = this->get_desired_info(query,"content");
    if(!(this->check_comment_errors(command,central_info)))   
        return false;
    if(content.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::process_reply(string command,MI& central_info)
{
    if(!(this->check_process_reply(command,central_info)))
        return ;
    string query = this->return_query(command);
    int film_id,comment_id;
    string content;
    if(this->get_desired_info(query,"film_id").size()!=0&&
    this->get_desired_info(query,"comment_id").size()!=0&&
    this->get_desired_info(query,"content").size()!=0)
    {
        film_id = stoi(this->get_desired_info(query,"film_id"));
        comment_id = stoi(this->get_desired_info(query,"comment_id"));
        content = this->get_desired_info(query,"content");
        central_manager->reply_to_a_comment_for_publisher(film_id,comment_id,content);
    }
}
void CommandProcessor::process_delete_comments(string command,MI& central_info)
{
    if(!(this->check_comment_errors(command,central_info)))
        return;
    string query = this->return_query(command);
    int film_id ,comment_id;
    if(this->get_desired_info(query,"film_id").size()!=0&&
    this->get_desired_info(query,"comment_id").size()!=0)
    {
        film_id = stoi(this->get_desired_info(query,"film_id"));
        comment_id = stoi(this->get_desired_info(query,"comment_id"));
        central_manager->remove_a_comment_for_publisher(film_id,comment_id);
    }
}
bool CommandProcessor::check_process_get_films(string command,MI central_info)
{
    if(central_info.system_sit==SYSTEM_QUIT||central_info.system_sit==NO_USER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    if(this->first_check(command))
        return true;
    return false;
}
bool CommandProcessor::first_check(string command)
{
    string query = this->return_query(command);
    string name = this->get_desired_info(query,"name");
    string min_rate = this->get_desired_info(query,"min_rate");
    string min_year = this->get_desired_info(query,"min_year");
    string price = this->get_desired_info(query,"price");
    string max_year = this->get_desired_info(query,"max_year");
    string director = this->get_desired_info(query,"director");
    string film_id = this->get_desired_info(query,"film_id");
    if(query.size()!=0&&name.size()==0&&min_rate.size()==0&&min_year.size()==0&&
    price.size()==0&&max_year.size()==0&&director.size()==0&&film_id.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::process_get_films_command(string command,MI& central_info)
{
    if(!(this->check_process_get_films(command,central_info)))
        return ;
    string query = this->return_query(command);
    int film_id;
    if(this->get_desired_info(query,"film_id").size()!=0)
    {
        film_id = stoi(this->get_desired_info(query,"film_id"));
        
        central_manager->show_film_details_for_user(film_id);
    }
    else 
    {
        string name,director;
        float min_rate;
        int min_year,price,max_year;
        if(this->get_desired_info(query,"name").size()!=0)
            name = this->get_desired_info(query,"name");
        if(this->get_desired_info(query,"min_rate").size()!=0)
            min_rate = stof(this->get_desired_info(query,"min_rate"));
        else 
            min_rate =0;
        if(this->get_desired_info(query,"min_year").size()!=0)
           min_year = stoi(this->get_desired_info(query,"min_year"));
        else 
            min_year = 0;
        if(this->get_desired_info(query,"price").size()!=0)
            price = stoi(this->get_desired_info(query,"price"));
        else 
            price = 0;
        if(this->get_desired_info(query,"max_year").size()!=0)
            max_year = stoi(this->get_desired_info(query,"max_year"));
        else 
            max_year = 0;
        if(this->get_desired_info(query,"director").size()!=0)
            director = this->get_desired_info(query,"director");
        central_manager->process_user_search(name,min_rate,min_year,price,max_year,director);
    }
}
bool CommandProcessor::edit_film_check(string command,MI central_info)
{
    if(central_info.system_sit!=PUBLISHER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string film_id = this->get_desired_info(query,"film_id");
    if(query.size()==0||film_id.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::edit_a_film_data_for_a_publisher(string command,MI& central_info)
{
    if(!(this->edit_film_check(command,central_info)))
        return;
    string query = this->return_query(command);
    int film_id = stoi(this->get_desired_info(query,"film_id"));
    Publisher* des_pub = central_manager->find_publisher_with_id(central_manager->get_client_id());
    Film* des_fil = central_manager->find_film_with_id(film_id);
    string name = this->get_desired_info(query,"name");
    string year = this->get_desired_info(query,"year");
    string length = this->get_desired_info(query,"length");
    string summary = this->get_desired_info(query,"summary");
    string director = this->get_desired_info(query,"director");
    central_manager->change_a_film_data(des_pub->get_id(),
    des_fil->get_id(),name,year,length,summary,director);
    cout<<"OK"<<endl;
}
bool CommandProcessor::add_film_check(string command,MI central_info)
{
    if(central_info.system_sit!=PUBLISHER_ONLINE)
    {
        throw AccessError();
        return false;
    }
    string query = this->return_query(command);
    string name = this->get_desired_info(query,"name");
    string year = this->get_desired_info(query,"year");
    string length = this->get_desired_info(query,"length");
    string price = this->get_desired_info(query,"price");
    string summary = this->get_desired_info(query,"summary");
    string director = this->get_desired_info(query,"director");
    if(name.size()==0||year.size()==0||length.size()==0||price.size()==0||
    summary.size()==0||director.size()==0||query.size()==0)
    {
        throw WrongRequest();
        return false;
    }
    return true;
}
void CommandProcessor::add_film_for_a_publisher(string command,MI& central_info)
{
    if(!(this->add_film_check(command,central_info)))
    {
        return;
    }
    string query = this->return_query(command);
    string name = this->get_desired_info(query,"name");
    int year =  stoi(this->get_desired_info(query,"year"));
    int length = stoi(this->get_desired_info(query,"length"));
    int price = stoi(this->get_desired_info(query,"price"));
    string summary = this->get_desired_info(query,"summary");
    string director = this->get_desired_info(query,"director");
    Film* new_film = new Film(central_info.current_user_id,name,
            central_info.central_film_id,ZERO,price,year,director,length,summary);
    for(int i=0;i<central_manager->get_data_base_all_publishers().size();i++)
    {
        if(central_info.current_user_id == central_manager->get_data_base_all_publishers()[i]->get_id())
        {
            central_manager->get_data_base_all_publishers()[i]->add_an_uploaded_film(new_film);
            central_manager->change_central_info(central_info,
            CENTRAL_FILM_ID,central_info.current_user_id,PUBLISHER_ONLINE);
            central_manager->get_data_base_all_publishers()[i]->send_new_film_notice();   
            central_manager->add_a_film_to_data_base(new_film);
            cout<<"OK"<<endl;
        }
    }
}
bool CommandProcessor::login_check(string command,MI central_info)
{
    string query = this->return_query(command);
    string username = this->get_desired_info(query,"username");
    string password = this->get_desired_info(query,"password");
    if(username.size()==0||password.size()==0||central_info.system_sit==NO_USER_ONLINE||query.size()==0)
        return false;
    long unsigned int hashed_password = this->hash_password(password.c_str());
    for(int i=0;i<central_manager->concat_user_vectors().size();i++)
    {
        if(central_manager->concat_user_vectors()[i]->get_username() == username)
        {
            if(central_manager->concat_user_vectors()[i]->get_password() == hashed_password)
                return true;
        }
    }
    throw WrongRequest();
    return false;
}
void CommandProcessor::login_user(string command,MI& central_info)
{
    if(!(this->login_check(command,central_info)))
    {
        throw WrongRequest();
        return ;
    }
    string query = this->return_query(command);
    string username = this->get_desired_info(query,"username");
    long unsigned int password = this->hash_password((this->get_desired_info(query,"password").c_str()));
    for(int i=0;i<central_manager->get_data_base_all_publishers().size();i++)
    {
        if(username == central_manager->get_data_base_all_publishers()[i]->get_username())
        {
            central_manager->change_central_info(central_info,
            SYSTEM_SIT,central_manager->get_data_base_all_publishers()[i]->get_id(),PUBLISHER_ONLINE);
            central_manager->set_client_data(central_manager->get_data_base_all_publishers()[i]->get_id(),
            central_manager->get_data_base_all_publishers()[i]->get_username(),
            central_manager->get_data_base_all_publishers()[i]->get_password(),
            central_manager->get_data_base_all_publishers()[i]->get_email(),
            central_manager->get_data_base_all_publishers()[i]->get_age(),true);
            cout<<"OK"<<endl;
            return ;
        }
    }       
    for(int i=0;i<central_manager->get_data_base_all_customers().size();i++)
    {
        if(username == central_manager->get_data_base_all_customers()[i]->get_username())
        {
            central_manager->change_central_info(central_info,
            SYSTEM_SIT,central_manager->get_data_base_all_customers()[i]->get_id(),CUSTOMER_ONLINE);
            central_manager->set_client_data(central_manager->get_data_base_all_customers()[i]->get_id(),
            central_manager->get_data_base_all_customers()[i]->get_username(),
            central_manager->get_data_base_all_customers()[i]->get_password(),
            central_manager->get_data_base_all_customers()[i]->get_email(),
            central_manager->get_data_base_all_customers()[i]->get_age(),false);
            cout<<"OK"<<endl;
            return ;
        }
    }
    throw WrongRequest();
}
bool CommandProcessor::is_email_valid(const std::string& email)
{
   const std::regex pattern
      ("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   return std::regex_match(email, pattern);
}