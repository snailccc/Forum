#ifndef PLATE_H
#define PLATE_H
#include "header.h"
#include "post.h"
#include<QPushButton>

class Plate:public QPushButton
{
private:
    string title;
    vector<Post>posts;
public:
    Plate(QWidget *parent, int id, string title);
};

#endif // PLATE_H
