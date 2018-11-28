#ifndef POST_H
#define POST_H
#include "header.h"
#include "comment.h"
#include <QDateTime>

class Post
{
private:
    string title,content;
    int timestamp, id;

public:
    Post(int id, string title, string content);
};

#endif // POST_H
