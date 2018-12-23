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
    int plateId, index;
    //网络连接部分
    QTcpSocket *socket;
    QTcpServer *server;
    qint64 bytesWritten;
    qint64 bytesWrite;
    qint64 bytesRecived;
    qint64 perDataSize;
    QByteArray inBlock;
    QByteArray outBlock;
public:
    PlateView(int index, QString title,int id,QTcpServer *server,QTcpSocket *socket,QWidget *parent=0);
    void Init_View();
    void Add(Post *post);
    void DeletePost(int postId);
    void newConnect();
    friend vector<Post*>& operator<<(vector<Post*>& group, QString db);
private slots:
    void on_pub_post_clicked(bool checked);
    void postDetail();
    void disconnectServer();
    void sendData(QString message);
    void receiveData();
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
    void Show(int index,QTcpServer *server,QTcpSocket *socket);
    int Id();
    PlateView *plateview;
};

/////////////////////PubView//////////////////////////

class PubView:public QDialog
{
    Q_OBJECT
private:
    Ui::Public *ui;
    QString title,content;
public:
    PubView(QWidget *parent=0);
    QString Title();
    QString Content();

private slots:
    void on_ok_clicked(bool checked);
};

#endif // PLATE_H
