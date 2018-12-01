#ifndef COMMENT_H
#define COMMENT_H
#include "header.h"
#include<QDateTime>
#include<QLabel>

class Comment:public QLabel
{
    Q_OBJECT
private:
    QString content;
    int time;
public:
    Comment(QWidget *parent,QString content);
};

#endif // COMMENT_H
