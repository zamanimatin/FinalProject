#include "manager.h"
void Manager::add_a_film_to_data_base(Film* f)
{
    int publisher_contribute = f->calc_publisher_share();
    publishers_contribution[f->get_publisher_id()].push_back(publisher_contribute);
    int rest = f->get_price() - publisher_contribute;
    this->increase_system_salary(rest);
    data_base_all_films.push_back(f);
    
}
void Manager::add_a_publisher_to_data_base(Publisher* p)
{
    data_base_all_publishers.push_back(p);
}
void Manager::set_client_data(int id,string username,int password,string email,int age,bool _sit)
{
    client_id = id;
    client_username = username;
    client_password = password;
    client_age = age;
    client_email = email;
    client_publisher_sit = _sit;
}
void Manager::add_a_customer_to_data_base(Customer* c)
{
    data_base_all_customers.push_back(c);
}
bool Manager::user_exists_with_name(string username)
{
    for(int i=0 ;i<data_base_all_customers.size();i++)
        if(data_base_all_customers[i]->get_username() == username)
            return true;
    for(int i=0;i<data_base_all_publishers.size();i++)
        if(data_base_all_publishers[i]->get_username() == username)
            return true;
    return false;
}
void Manager::set_data_base_info(vector<Film*> newfilms,vector<Publisher*> newpublishers
,vector<Customer*> newcustomers)
{
    data_base_all_films = newfilms;
    data_base_all_publishers = newpublishers;
    data_base_all_customers = newcustomers;
}   
MI Manager::change_central_info(MI& central_info,string data,int user_id,int new_system_sit)
{
    if(data == CENTRAL_CLIENT_ID)
        central_info.central_client_id++;
    else if(data == CENTRAL_FILM_ID)
        central_info.central_film_id++;
    else if(data == CENTRAL_COMMENT_ID)
        central_info.central_comment_id++;
    else if(data == CENTRAL_MESSAGE_ID)
        central_info.central_message_id++;
    else if(data == SYSTEM_SIT)
    {
        central_info.system_sit = new_system_sit;
    }
    central_info.current_user_id = user_id;
    return central_info;
}
vector<User*> Manager::concat_user_vectors()
{
    vector<User*> all_users;
    for(int i=0;i<data_base_all_publishers.size();i++)
        all_users.push_back(data_base_all_publishers[i]);
    for(int i=0;i<data_base_all_customers.size();i++)
        all_users.push_back(data_base_all_customers[i]);
    return all_users;
}
void Manager::increase_system_salary(int system_share)
{
    system_salary += system_share;
}
User* Manager::find_user_with_id(int id)
{
    vector<User*> all_users = this->concat_user_vectors();
    for(int i=0;i<all_users.size();i++)
    {
        if(all_users[i]->get_id()==id)
            return all_users[i];
    }
}
Film* Manager::find_film_with_id(int id)
{
    for(int i=0;i<data_base_all_films.size();i++)
    {
        if(data_base_all_films[i]->get_id()==id)
            return data_base_all_films[i];
    }
    throw ExistenceError();
}
void Manager::show_read_notices_for_user(int limit)
{
    User* desired = this->find_user_with_id(client_id);
    desired->show_reads(limit);
}
void Manager::show_unread_notices_for_user(string command)
{
    User* desired = this->find_user_with_id(client_id);
    desired->show_unreads();
}
void Manager::show_user_purchased_films(string name,int price,int min_year,int max_year,string director)
{
    User* desired = this->find_user_with_id(client_id);
    desired->show_purchased_films(name,price,min_year,max_year,director);
}
void Manager::comment_on_a_film_for_user(int film_id,string content)
{
    User* desired = this->find_user_with_id(client_id);
    vector<Film*>user_films = desired->get_bought_films();
    Film* desired_film;
    if(desired->does_have_film(film_id))   
    {
        desired_film = this->find_film_with_id(film_id);
        desired_film->add_a_comment(desired->get_id(),content);
        User* publisher = this->find_user_with_id(desired_film->get_publisher_id());
        publisher->add_an_unread_notice("User "+
        desired->get_username()+" with id "+to_string(desired->get_id())+
        " comment on your film "+desired_film->get_name()+" with id "+
        to_string(desired_film->get_id())+" .");
    }
}
void Manager::rate_a_film_for_user(int film_id,float score)
{
    User* desired = this->find_user_with_id(client_id);
    vector<Film*>user_films = desired->get_bought_films();
    Film* desired_film;
    if(desired->does_have_film(film_id))
    {
        desired_film = this->find_film_with_id(film_id);
        desired_film->set_new_rate(score);
        User* publisher = this->find_user_with_id(desired_film->get_publisher_id());
        publisher->add_an_unread_notice("User "+desired->get_username()+" with id "
        +to_string(desired->get_id())+" rate your film "+desired_film->get_name()+" with id "
        +to_string(desired_film->get_id()));
    }
}
bool Manager::is_film_exists(int film_id)
{
    for(int i=0;i<data_base_all_films.size();i++)
    {
        if(data_base_all_films[i]->get_id()==film_id)
            return true;
    }
    return false;
}
void Manager::buy_film_for_user(int film_id)
{
    User* desired = this->find_user_with_id(client_id);
    vector<Film*>user_films = desired->get_bought_films();
    Film* desired_film;
    if(this->is_film_exists(film_id))
    {
        desired_film = this->find_film_with_id(film_id);
        desired->add_bought_film(desired_film);
        desired->decrease_money(desired_film->get_price());
        this->add_money_for_publisher_contribute(desired_film->get_publisher_id(),film_id);
        int system_share = desired_film->get_price()-desired_film->calc_publisher_share();
        this->increase_system_salary(system_share);
    }
}
void Manager::add_money_for_publisher_contribute(int publisher_id,int film_id)
{
    User* publisher = this->find_user_with_id(publisher_id);
    Film* desired_film = this->find_film_with_id(film_id);
    int publisher_share = desired_film->calc_publisher_share();
    publishers_contribution[publisher_id].push_back(publisher_share);
}
void Manager::show_film_comments(int fid)
{
    int i=1;
    for(int i=0;i<data_base_all_films.size();i++)
    {
        if(data_base_all_films[i]->get_id()==fid)
        {
            Film* des = data_base_all_films[i];
            map<int,map<int,string >> comments;
            comments = des->get_comments();
            for(auto iter=comments.begin();iter!=comments.end();iter++)
            {
                cout<<iter->first<<i<<". "<<comments[i].at(ZERO);
            }
        }
    }
}
void Manager::show_film_details_for_user(int film_id)
{
    Film* desired_film = this->find_film_with_id(film_id);
    desired_film->show_deteils();
    // desired_film->show_comments();
    this->show_film_comments(film_id);
    this->show_recommends(desired_film->get_id());
}
void Manager::show_recommends(int film_id)
{
    cout<<"Recommendation Film"<<endl;
    cout<<"#. Film Id | Film Name | Film Length | Film Director"<<endl;
    vector<Film*> recommened_films = this->find_top_four_films(film_id);
    for(int i=0;i<FOUR;i++)
    {
        cout<<i+1<<". "<<recommened_films[i]->get_id()<<" | ";
        cout<<recommened_films[i]->get_name()<<" | ";
        cout<<recommened_films[i]->get_lenght()<<" | ";
        cout<<recommened_films[i]->get_director()<<endl;
    }
}
Film* Manager::find_film_with_highest_rate(vector<Film*>all_films)
{
    Film*desired = all_films[0];
    for(int i=0;i<all_films.size();i++)
    {
        if(all_films[i]->get_rate()>desired->get_rate())
            desired = all_films[i];
    }
    return desired;
}
vector<Film*> Manager::find_top_four_films(int film_id)
{
    vector<Film*> all_films = data_base_all_films;
    vector<Film*> desired_films;
    for(int i=0;desired_films.size()!=4;i++)
    {
        Film* highest_rate = this->find_film_with_highest_rate(all_films);
        if(highest_rate->get_id()!=film_id)
        {
            desired_films.push_back(highest_rate);
            all_films = this->erase_film_with_id(highest_rate->get_id(),all_films);
        }
    }
    return desired_films;
}
vector<Film*> Manager::erase_film_with_id(int film_id,vector<Film*>&all_films)
{
    for(int i=0;i<all_films.size();i++)
    {
        if(all_films[i]->get_id()==film_id)
        {
            all_films.erase(all_films.begin()+i);
            return all_films;
        }
    }
}
vector<Film*> Manager::make_all_filtered_films(string name,float min_rate,
int min_year,int price,int max_year,string director)
{
    vector<Film*> desired_films;
    for(int i=0;i<data_base_all_films.size();i++)
    {
        if(data_base_all_films[i]->get_name()==name&&data_base_all_films[i]->get_rate()>=min_rate
        &&data_base_all_films[i]->get_year()>=min_year&&data_base_all_films[i]->get_year()<=max_year
        &&data_base_all_films[i]->get_director()==director&&data_base_all_films[i]->get_price()==price)
            desired_films.push_back(data_base_all_films[i]);
    }
    if(desired_films.size()==0)
        throw ExistenceError();
    return desired_films;
}
void Manager::remove_a_film_for_publisher(int film_id)
{
    for(int i=0;i<data_base_all_publishers.size();i++)
    {
        if(data_base_all_publishers[i]->get_id()==client_id)
        {
            for(int j=0;j<data_base_all_publishers[i]->get_uploaded_films().size();j++)        
            {
                if(data_base_all_publishers[i]->get_uploaded_films()[j]->get_id()==film_id)
                {
                    vector<Film*>des = data_base_all_publishers[i]->get_uploaded_films();
                    int fid = des[j]->get_id();
                    des.erase(des.begin()+j);
                    data_base_all_publishers[i]->set_uploaded_films(des);
                    this->remove_film_from_all_with_id(fid);
                }
            }
        }
    }
}
void Manager::remove_film_from_all_with_id(int fid)
{
    for(int i=0;i<data_base_all_films.size();i++)
    {
        if(data_base_all_films[i]->get_id()==fid)
        {
            vector<Film*>des = data_base_all_films;
            des.erase(des.begin()+i);
            this->set_data_base_film(des);
        }
    }
}
void Manager::show_all_filter_activated_films(vector<Film*>films)
{
    for(int i=0;i<films.size();i++)
    {
        cout<<i+1<<". "<<films[i]->get_id()<<" | "<<films[i]->get_name()<<" | ";
        cout<<films[i]->get_lenght()<<" | "<<films[i]->get_price()<<" | ";
        cout<<films[i]->get_rate()<<" | "<<films[i]->get_year()<<" | ";
        cout<<films[i]->get_director()<<endl;
    }
}
void Manager::show_all_system_films()
{
    cout<<"#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director"<<endl;
    vector<Film*> desired_films = data_base_all_films;
    for(int i=0;i<data_base_all_films.size();i++)
    {
        cout<<i+1<<". "<<desired_films[i]->get_id()<<" | "<<desired_films[i]->get_name()<<" | ";
        cout<<desired_films[i]->get_lenght()<<" | "<<desired_films[i]->get_price()<<" | ";
        cout<<desired_films[i]->get_rate()<<" | "<<desired_films[i]->get_year()<<" | ";
        cout<<desired_films[i]->get_director()<<endl;
    }
}
void Manager::process_user_search(string name, float min_rate
,int min_year,int price,int max_year,string director)
{
    vector<Film*> desired_films;
    if(name.size()!=0&&min_rate!=0&&min_year!=0&&price!=0&&max_year!=0&&director.size()!=0)
    {
        this->show_all_filter_activated_films(this->make_all_filtered_films(name,min_rate
        ,min_year,price,max_year,director));
    }
    else if(name.size()==0&&min_rate==0&&min_year==0&&price==0&&max_year==0&&director.size()==0)
    {
        this->show_all_system_films();
    }
    else 
    {
        this->show_system_films_semi_filtered(name,min_rate,min_year,price,max_year,director);
    }
}
void Manager::show_system_films_semi_filtered(string name,float min_rate,
int min_year,int price,int max_year,string director)
{
    cout<<"#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director"<<endl;
    vector<Film*>desired_films = data_base_all_films;
    try
    {
        desired_films = this->find_films_semi_filtered(name,min_rate,
        min_year,price,max_year,director,desired_films);  
    }catch(exception& ex)
    {
        throw;
        return ;
    }
    for(int i=0;i<desired_films.size();i++)
    {
        cout<<i+1<<desired_films[i]->get_id()<<" | "<<desired_films[i]->get_name()<<" | ";
        cout<<desired_films[i]->get_lenght()<<" | "<<desired_films[i]->get_price()<<" | ";
        cout<<desired_films[i]->get_rate()<<" | "<<desired_films[i]->get_year()<<" | ";
        cout<<desired_films[i]->get_director()<<endl;
    }
}
void Manager::reply_to_a_comment_for_publisher(int film_id,int comment_id,string content)
{
    Publisher* des_publisher = this->find_publisher_with_id(client_id);
    Film* des_film =this->find_film_with_id(film_id);
    for(int i=0;i<des_publisher->get_uploaded_films().size();i++)
    {
        if(des_publisher->get_uploaded_films()[i]->get_id() == film_id)
        {
            des_publisher->get_uploaded_films()[i]->add_a_respond(
                des_film->find_commenter_id_with_comment_id(comment_id),content);
            User* des_user = this->find_user_with_id(des_film->find_commenter_id_with_comment_id(comment_id));
            des_user->add_an_unread_notice("Publisher "+ des_publisher->get_username()+" with id " +
            to_string(des_publisher->get_id())+" reply to your comment");
            return;
        }
    }
    throw AccessError();
}
void Manager::remove_a_comment_for_publisher(int film_id,int comment_id)
{
    Publisher* des_publisher = this->find_publisher_with_id(client_id);
    Film* desired_film = this->find_film_with_id(film_id);
    for(int i=0;i<des_publisher->get_uploaded_films().size();i++)
    {
        if(des_publisher->get_uploaded_films()[i]->get_id() == film_id)
        {
            des_publisher->get_uploaded_films()[i]->delete_a_comment_with_id(comment_id);
            des_publisher->get_uploaded_films()[i]->delete_a_comment_related_responds(comment_id);
        }
        else
            throw AccessError();
    }
}
Publisher* Manager::find_publisher_with_id(int publisher_id)
{
    for(int i=0;i<data_base_all_publishers.size();i++)
        if(data_base_all_publishers[i]->get_id()==publisher_id)
            return data_base_all_publishers[i];
}
void Manager::follow_a_publisher_for_a_customer(int publisher_id)
{
    for(int i=0;i<data_base_all_publishers.size();i++)
    {
        if(data_base_all_publishers[i]->get_id()==publisher_id)
        {
            User* desired_customer;
            User* desired_publisher = data_base_all_publishers[i];           
            for(int j=0;j<data_base_all_customers.size();j++)
            {
                if(data_base_all_customers[j]->get_id()==client_id)   
                {
                    desired_customer = data_base_all_customers[j];
                    desired_customer->add_a_publisher(desired_publisher);
                    data_base_all_publishers[i]->add_an_unread_notice("User " +
                     desired_customer->get_username()+" with id "+ 
                     to_string(desired_customer->get_id())+" follow you.");
                }
            }
        }
    }
}
void Manager::show_publisher_uploaded_films(string name,float min_rate,
int min_year,int price,int max_year,string director)
{
    if(name.size()!=0&&min_rate!=0&&min_year!=0&&price!=0&&max_year!=0&&director.size()!=0)
    {
        this->show_publisher_films_all_filtered(name,min_rate,min_year,price,max_year,director);
    }
    else if(name.size()==0&&min_rate==0&&min_year==0&&price==0&&max_year==0&&director.size()==0)
    {
        this->show_publisher_all_films();
    }
    else
    {
        this->show_publisher_films_semi_filtered(name,min_rate,min_year,price,max_year,director);
    }   
}
void Manager::show_publisher_all_films()
{
    cout<<"#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director"<<endl;
    Publisher* des_pub = this->find_publisher_with_id(client_id);
    vector<Film*>desired_films = des_pub->get_uploaded_films();
    for(int i=0;i<des_pub->get_uploaded_films().size();i++)
    {
        cout<<i+1<<". "<<desired_films[i]->get_id()<<" | "<<desired_films[i]->get_name()<<" | ";
        cout<<desired_films[i]->get_lenght()<<" | "<<desired_films[i]->get_price()<<" | ";
        cout<<desired_films[i]->get_rate()<<" | "<<desired_films[i]->get_year()<<" | ";
        cout<<desired_films[i]->get_director()<<endl;
    }
}
void Manager::show_publisher_films_semi_filtered(string name,float min_rate,
int min_year,int price,int max_year,string director)
{
    cout<<"#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director"<<endl;
    Publisher* des_pub = this->find_publisher_with_id(client_id);
    vector<Film*>desired_films = des_pub->get_uploaded_films();
    try
    {
        desired_films = this->find_films_semi_filtered(name,min_rate,
        min_year,price,max_year,director,desired_films);  
    }catch(exception& ex)
    {
        throw;
        return ;
    }
    for(int i=0;i<desired_films.size();i++)
    {
        cout<<i+1<<desired_films[i]->get_id()<<" | "<<desired_films[i]->get_name()<<" | ";
        cout<<desired_films[i]->get_lenght()<<" | "<<desired_films[i]->get_price()<<" | ";
        cout<<desired_films[i]->get_rate()<<" | "<<desired_films[i]->get_year()<<" | ";
        cout<<desired_films[i]->get_director()<<endl;
    }
}
vector<Film*> Manager::find_films_semi_filtered(string name,float min_rate,
int min_year,int price,int max_year,string director,vector<Film*>films)
{
    vector<Film*> desired_films;
    desired_films = films;
    if(name.size()!=0)
        desired_films = this->find_desired_films_with_name(name,desired_films);
    if(min_rate!=0)
        desired_films = this->find_desired_films_with_min_rate(min_rate,desired_films);
    if(min_year!=0)
        desired_films = this->find_desired_films_with_min_year(min_year,desired_films);
    if(price!=0)
        desired_films = this->find_desired_films_with_price(price,desired_films);
    if(max_year!=0)
        desired_films = this->find_desired_films_with_max_year(max_year,desired_films);
    if(director.size()!=0)
        desired_films = this->find_desired_films_with_director(director,desired_films);
    return desired_films;
}
vector<Film*>  Manager::find_desired_films_with_name(string name,vector<Film*>desired)
{
    vector<Film*> films;
    int count = 0;
    for(int i=0;i<desired.size();i++)
    {
        if(desired[i]->get_name()==name)
        {
            films.push_back(desired[i]);
            count++;
        }
    }
    if(this->check_existence_error_throw(count))
        return films;
}
vector<Film*> Manager::find_desired_films_with_min_rate(float min_rate,vector<Film*>desired)
{
    vector<Film*> films;
    int count =0;
    for(int i=0;i<desired.size();i++)
    {
        if(desired[i]->get_rate()>=min_rate)
        {
            films.push_back(desired[i]);
            count++;
        }
    }
    if(this->check_existence_error_throw(count))
        return films;
}
int Manager::check_existence_error_throw(int count)
{
    if(count==0)
    {
        throw ExistenceError();
        return 0;
    }
}
vector<Film*> Manager::find_desired_films_with_min_year(int min_year,vector<Film*>desired)
{
    vector<Film*> films;
    int count = 0;
    for(int i=0;i<desired.size();i++)
    {
        if(desired[i]->get_year()>=min_year)
        {
            films.push_back(desired[i]);
            count++;
        }
    }
    if(this->check_existence_error_throw(count))
        return films;
}
vector<Film*> Manager::find_desired_films_with_price(int price,vector<Film*>desired)
{
    vector<Film*> films;
    int count =0;
    for(int i=0;i<desired.size();i++)
    {
        if(desired[i]->get_price()==price)
        {
            films.push_back(desired[i]);
            count++;
        }
    }
    if(this->check_existence_error_throw(count))
        return films;
}
vector<Film*> Manager::find_desired_films_with_max_year(int max_year,vector<Film*>desired)
{
    vector<Film*> films;
    int count =0;
    for(int i=0;i<desired.size();i++)
    {
        if(desired[i]->get_year()<=max_year)
        {
            films.push_back(desired[i]);
            count++;
        }
    }
    if(this->check_existence_error_throw(count))
        return films;
}
vector<Film*> Manager::find_desired_films_with_director(string director,vector<Film*>desired)
{
    vector<Film*> films;
    int count = 0;
    for(int i=0;i<desired.size();i++)
    {
        if(desired[i]->get_director()==director)
        {
            films.push_back(desired[i]);
            count++;
        }
    }
    if(this->check_existence_error_throw(count))
        return films;
}
void Manager::show_publisher_films_all_filtered(string name,float min_rate,int min_year,int price,int max_year,string director)
{
    cout<<"#. Film Id | Film Name | Film Length | Film price | Rate | Production Year | Film Director"<<endl;
    Publisher* des_pub = this->find_publisher_with_id(client_id);
    for(int i=0;i<des_pub->get_uploaded_films().size();i++)
    {
        int j=1;
        Film* desired = des_pub->get_uploaded_films()[i];
        if(desired->get_name()==name&&desired->get_rate()==min_rate&&
        desired->get_year()>=min_year&&desired->get_year()<=max_year&&desired->get_director()==director)
        {
            cout<<j<<". "<<desired->get_id()<<" | "<<desired->get_name()<<" | ";
            cout<<desired->get_lenght()<<" | "<<desired->get_price()<<" | ";
            cout<<desired->get_rate()<<" | "<<desired->get_year()<<" | "<<desired->get_director()<<endl;
            j++;
        }
    }
}
void Manager::show_publisher_follow_list()
{
    Publisher* des_publisher = this->find_publisher_with_id(client_id);
    des_publisher->show_list_of_followers();
}
void Manager::increase_publisher_money(int amount,int publisher_id)
{
    for(int i=0;i<data_base_all_publishers.size();i++)
        if(data_base_all_publishers[i]->get_id()==publisher_id)
            data_base_all_publishers[i]->increase_money(amount);
}
void Manager::increase_user_money(int amount,MI central_info)
{  
    if(central_info.system_sit==CUSTOMER_ONLINE)
    {
        for(int i=0;i<data_base_all_customers.size();i++)
        {
            if(data_base_all_customers[i]->get_id()==client_id)
            {
                data_base_all_customers[i]->increase_money(amount);
                cout<<"OK"<<endl;
                return ;
            }
        }
    }
    for(int i=0;i<data_base_all_publishers.size();i++)
    {
        if(data_base_all_publishers[i]->get_id()==client_id)
        {
            data_base_all_customers[i]->increase_money(amount);
            return;
        }
    }
}
void Manager::get_publisher_his_share(int publisher_id)
{
    vector<int> salary;
    for(auto iter = publishers_contribution.begin();iter!=publishers_contribution.end();iter++)
    {
        if(iter->first==publisher_id)
        {
            salary = iter->second;
            iter->second.clear();
        }
    }
    int money;
    for(int i=0;i<salary.size();i++)
        money+=salary[i];
    this->increase_publisher_money(money,publisher_id);
}
void Manager::change_a_film_data(int Pub_id,int fil_id,string name,
string year,string length,string summary,string director)
{
    for(int i=0;i<data_base_all_publishers.size();i++)
        if(data_base_all_publishers[i]->get_id()==Pub_id)
            data_base_all_publishers[i]->edit_a_film(fil_id,name,year,length,summary,director);
}