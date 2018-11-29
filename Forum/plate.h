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
    PostGroup *postgroup;
    Plate(QWidget *parent, int id, QString title);
    Q_INVOKABLE QString get_title(){return title;}
    Q_INVOKABLE int get_id(){return id;}

private:
    int id;
    QString title;

signals:

public slots:
};

#endif // PLATE_H
