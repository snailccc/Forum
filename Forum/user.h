#ifndef USER_H
#define USER_H
#include<iostream>
using namespace std;

class User
{
private:
    string id,userName, password;
public:
    User(string id,string password);
    ViewInfo();
    ~User();
};

#endif // USER_H
