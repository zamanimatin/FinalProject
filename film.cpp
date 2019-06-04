#include "film.h"
Film::Film(int _publisher_id,string _name,int _id,float _rate,int _price,int _year,string _director,
int _length,string _summary)
{
    publisher_id = _publisher_id; 
    name = _name;
    id = _id;
    rate = _rate;
    price = _price;
    year = _year;
    director = _director;
    length = _length;
    summary = _summary;
}
void Film::change_film_info(string film_name ,string film_year ,
string film_length ,string film_summary ,string film_director)
{
    if(film_name.size()!=0 )
        name = film_name;
    if(film_year.size() != 0)
        year = stoi(film_year);
    if(film_length.size() != 0)
        length = stoi(film_length);
    if(film_summary.size() != ZERO )
        summary = film_summary;
    if(film_director.size() != ZERO)
        director = film_director;
}
int Film::get_film_situation()
{
    if(rate < FIVE)
        return AWFUL;
    else if(rate >= FIVE &&rate < EIGHT)
        return GOOD;
    else if(rate >= EIGHT)
        return GREAT;
}
int Film::calc_publisher_share()
{
    switch(this->get_film_situation())
    {
        case AWFUL:
            return EIGHTY_PERCENT * price;
        break;
        case GOOD:
            return NINTY_PERCENT * price;
        break;
        case GREAT:
            return NINTY_FIVE_PERCENT * price;
        break;
    }
}
void Film::add_a_comment(int commenter_id,string content)
{
    int id = this->get_last_comment_id();
    id++;
    comments[id].insert({commenter_id,content});
}
void Film::add_a_respond(int related_commenter_id,string respond)
{
    int id = this->get_last_respond_id();
    id++;
    responds[id].insert({related_commenter_id,respond});
}
int Film::get_last_comment_id()
{  
    if(comments.size()!=0)
        return comments.rbegin()->first;
    else
        return ONE;
}
int Film::get_last_respond_id()
{
    if(responds.size()!=0)
        return responds.rbegin()->first;
    else
        return ONE;
}
void Film::set_new_rate(float _rate)
{
    float prev = rate*num_rater;
    prev+=_rate;
    this->increase_raters();
    rate = prev/num_rater;
}
void Film::show_deteils()
{
    cout<<"Details of Film "<<name<<endl;
    cout<<"Id = "<<id<<endl;
    cout<<"Director = "<<director<<endl;
    cout<<"Length = "<<length<<endl;
    cout<<"Year = "<<year<<endl;
    summary = this->make_summary_to_desired(summary);
    cout<<"Summary = "<<summary<<endl;
    cout<<"Rate = "<<rate<<endl;
    cout<<"Price = "<<price<<endl;
    cout<<endl;
    this->show_comments();
    cout<<endl;    
}
string Film::make_summary_to_desired(string summary)
{
    for(int i=0;i<summary.size();i++)
    {
        if(summary[i]==' ')
            summary[i]=LINE_MARK;
    }
    return summary;
}
void Film::show_comments()
{
    cout<<"Comments"<<endl;
    for(auto iter1 = comments.begin();iter1!=comments.end();iter1++)
    {
        cout<<iter1->first;
        map<int ,string> usr_comments = iter1->second;
        for(auto iter2 = usr_comments.begin();iter2!=usr_comments.end();iter2++)
        {
            cout<<". "<<iter2->second<<endl;
            this->show_responds(iter1->first);
        }
    }
    cout<<endl;
}
void Film::show_responds(int comment_id)
{
    int i=1;
    map<int ,string> usr_responds = responds.at(comment_id);
    for(auto iter = usr_responds.begin();iter!=usr_responds.end();iter++)
    {
        cout<<comment_id<<i<<"."<<". "<<iter->second<<endl;
    }
}
void Film::delete_a_comment_with_id(int id)
{
    for(auto iter = comments.begin();iter!=comments.end();iter++)
        if(iter->first==id)
        {
            comments.erase(iter);
            return ;
        }
}
void Film::delete_a_comment_related_responds(int comment_id)
{
    for(auto iter = responds.begin();iter!=responds.end();iter++)       
        if(iter->first==comment_id)
        {
            responds.erase(iter);
            return ;
        }
}
int Film::find_commenter_id_with_comment_id(int comment_id)
{
    map <int ,string> des_comments;
    for(auto iter = comments.begin();iter!=comments.end();iter++)
    {
        if(iter->first==comment_id)
        {
            des_comments = iter->second;
            auto iter1 = des_comments.begin();
            return iter1->first;
        }
    }
}
