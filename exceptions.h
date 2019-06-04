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
    const char* message = "Bad Request";
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
class NotEqualPassError : public std::exception
{
public:
    NotEqualPassError(){}
    virtual const char* what() const throw() {return message;}
private:
    const string type = "Not Equal Pass Error";
    const char* message = "Your password and re-password are not equal,Try again!";
};
class NotValidEmailError : public std::exception
{
public:
    NotValidEmailError(){}
    virtual const char* what() const throw() {return message;}
private:
    const string type = "Not Valid Email";
    const char* message = "Your email is not valid!";
};
class EmptyFieldError : public std::exception
{
public:
    EmptyFieldError(){}
    virtual const char* what() const throw() {return message;}
private:
    const string type = "Empty Field Error";
    const char* message = "One of the field is empty!";
};
class UsernameError : public std::exception
{
public:
    UsernameError(){}
    virtual const char* what() const throw() {return message;}
private:
    const string type = "Username Error";
    const char* message = "Username entered maybe used by other user,or you're using 'admin' username!";
};
#endif