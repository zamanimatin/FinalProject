#ifndef INFO_H
#define INFO_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cmath>
#include <map>
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10
#define PUT_STRING "PUT"
#define GET_STRING "GET"
#define DELETE_STRING "DELETE"
#define POST_STRING "POST"
#define QUESTION_MARK '?'
#define LINE_MARK '|'
#define AWFUL 0
#define GOOD 1
#define GREAT 2
#define EIGHTY_PERCENT 0.8
#define NINTY_PERCENT 0.9
#define NINTY_FIVE_PERCENT 0.95
#define CENTRAL_CLIENT_ID "central_client_id"
#define CENTRAL_MESSAGE_ID "central_message_id"
#define CENTRAL_FILM_ID "central_film_id"
#define CENTRAL_COMMENT_ID "central_comment_id"
#define SYSTEM_SIT "system_sit"
#define CURRENT_USER_ID "current_user_id"
#define CENTRAL_SESSION_ID "central_session_id"
#define PUBLISHER_ONLINE 1
#define CUSTOMER_ONLINE 2
#define ADMIN_ONLINE 3
#define ADMIN_USER_ID 0
#define ADMIN_EMAIL "admin@gmail.com"
#define NO_USER_ONLINE 0
#define SYSTEM_QUIT -1
using namespace std;
typedef struct main_info MI;
typedef struct related_info RI;
struct main_info
{
    int system_sit = 0;
    int current_user_id;
    int central_client_id = 1;
    int central_film_id = 1;
    int central_comment_id = 1;
    int central_message_id = 1;
    int central_session_id = 1;
};

#endif