#ifndef PLATE_H
#define PLATE_H
#include "header.h"
#include "post.h"
#include<QPushButton>
#include<QMetaObject>

class Plate : public QPushButton
{
    Q_OBJECT
public:
    Plate(QWidget *parent, int id, string title);
    inline string get_title(){return title;}
    inline int get_id(){return id;}

private:
    int id;
    string title;
    vector<Post>posts;

signals:

public slots:
};

#endif // PLATE_H
