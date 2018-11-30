#include "user.h"

User::User(QString id,QString password):
    id(id),password(password)
{

}

QString User::ID()
{
    return id;
}
