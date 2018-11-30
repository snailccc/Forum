#ifndef USER_H
#define USER_H

#include "header.h"

class User
{
private:
    QString id,userName, password;
public:
    User(QString id,QString password);
    QString ID();
    ViewInfo();
    ~User();
};

#endif // USER_H
