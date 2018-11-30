#ifndef PLATE_H
#define PLATE_H
#include "header.h"
#include "post.h"
#include "ui_plate.h"
#include<QPushButton>
#include<QMetaObject>
#include<QDialog>

class Plate;
class Plate_View;

//////////////////Plate_View//////////////////////////
class Plate_View:public QDialog{
private:
    QString title;
    vector<Post*>postgroup;
    Ui::Plate *ui;
public:
    Plate_View(QWidget *parent,QString title);
    void Init_View();
    void Add(Post *post);
    void Delete();
};

//////////////////Plate//////////////////////////

class Plate : public QPushButton
{
    Q_OBJECT
public:
//    PostGroup *postgroup;
    Plate(QWidget *parent, int id, QString title);
    Q_INVOKABLE QString get_title(){return title;}
    Q_INVOKABLE int get_id(){return id;}
    void AddPost(Post *post);
    void DeletePost(int id);
    void Show();

private:
    int id;
    QString title;
    Plate_View *view;

signals:

public slots:

};

#endif // PLATE_H
