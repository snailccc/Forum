#ifndef PLATE_H
#define PLATE_H
#include "header.h"
#include "post.h"
#include "user.h"
#include "ui_plate.h"
#include "ui_public.h"
#include<QPushButton>
#include<QMetaObject>
#include<QDialog>

class Plate;
class Plate_View;
class Pub_View;
class Post_Mange_View;

/////////////////////Pub_View//////////////////////////

class Pub_View:public QDialog
{
    Q_OBJECT
private:
    Ui::Public *ui;
    QString title,content;

public:
    Pub_View(QWidget *parent);
    QString Title();
    QString Content();

private slots:
    void on_ok_clicked(bool checked);
};

//////////////////Plate_View//////////////////////////
class Plate_View:public QDialog{
    Q_OBJECT
private:
    QString title;
    vector<Post*>postgroup;
    Ui::Plate *ui;
    Pub_View *pub_view;
    int plateId;
public:
    Plate_View(QWidget *parent,QString title,int id);
    void Init_View();
    void Add(Post *post);
    void Delete(int postId);
private slots:
    void on_pub_post_clicked(bool checked);
    void postDetail();
};

//////////////////Plate//////////////////////////

class Plate : public QPushButton
{
    Q_OBJECT
public:
    Plate(QWidget *parent, int id, QString title);
    Q_INVOKABLE QString get_title(){return title;}
    Q_INVOKABLE int get_id(){return id;}
    void AddPost(Post *post);
    void DeletePost(int id);
    void Show();
    int Id();

private:
    int id;
    QString title;
    Plate_View *view;

signals:

public slots:


};

//////////////////////Post_Mange_View/////////////////////
class Post_Mange_View:public QDialog
{
private:

};

#endif // PLATE_H
