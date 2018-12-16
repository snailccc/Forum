#ifndef PLATE_H
#define PLATE_H

#include "global.h"
#include "post.h"
#include "user.h"
#include "ui_plate.h"
#include "ui_public.h"
#include<QPushButton>
#include<QMetaObject>
#include<QDialog>

class Plate;
class PlateView;
class PubView;
class Post_Mange_View;


//////////////////PlateView//////////////////////////
class PlateView:public QDialog{
    Q_OBJECT
private:
    QString title;
    vector<Post*>postgroup;
    Ui::Plate *ui;
    PubView *pub_view;
    int plateId;
public:
    PlateView(QString title,int id,QWidget *parent=0);
    void Init_View();
    void Add(Post *post);
    void Delete(int postId);
    friend vector<Post*>& operator<<(vector<Post*>& group, QString db);
    friend Post*& operator>>(Post*& post1,QSqlDatabase db);
private slots:
    void on_pub_post_clicked(bool checked);
    void postDetail();
};


////////////////////Plate///////////////////////////
class Plate:public QPushButton
{
    Q_OBJECT
private:
    int id;
    QString title;
public:
    Plate();
    Plate(int id, QString title, QWidget *parent=0);
    QString get_title(){return title;}
    int get_id(){return id;}
//    void AddPost(Post *post);
//    void DeletePost(int id);
    void Show();
    int Id();
    PlateView *plateview;
//    QPushButton *plateButton;
};

/////////////////////PubView//////////////////////////

class PubView:public QDialog
{
    Q_OBJECT
private:
    Ui::Public *ui;
    QString title,content;

public:
    PubView(QWidget *parent);
    QString Title();
    QString Content();

private slots:
    void on_ok_clicked(bool checked);
};

#endif // PLATE_H
