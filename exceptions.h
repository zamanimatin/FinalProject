#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>
#include <exception>
#include "info.h"
using namespace std;
class ExistenceError : public std::exception
{
public: 
    ExistenceError(){}
    virtual const char* what() const throw() {return message;}
private:
    const string type = "Existence Error";
    const char* message = "Not Found";

};
class WrongRequest : public std::exception
{
public:
    WrongRequest(){}
    virtual const char* what() const throw() {return message;}
private:
    const string type = "Wrong Request";
    const char* message = "Bad request";
};
class AccessError : public std::exception
{
public:
    AccessError(){}
    virtual const char* what() const throw() {return message;}
private:
    const string type = "Access Error";
    const char* message = "Permission Denied";
};
#endif