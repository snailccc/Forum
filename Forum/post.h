#ifndef POST_H
#define POST_H
#include "header.h"
#include "comment.h"
#include<QDateTime>
#include<QAbstractListModel>
#include<QStringList>
#include<QObject>
#include<QVariant>
#include<QPushButton>

class Post:public QPushButton
{
private:
    QString title,content;
    int timestamp, id;

public:
    Post(QWidget *parent, int id, QString title, QString content);
    Q_INVOKABLE QString Title()const{return title;}
    Q_INVOKABLE int ID()const{return id;}
    Q_INVOKABLE QString Content()const{return content;}

//private slots:
//    void Detail();
};

////////////////////////////////PostGroup////////////////////////////////////////

//class PostGroup:public QAbstractListModel
//{
//public:
//    enum PostRoles {
//        TitleRole = Qt::UserRole + 1,
//        ContentRole,
//        IDRole
//    };

//    PostGroup(QObject *parent = 0);

//    void AddPost(const Post &post);

//    int rowCount(const QModelIndex & parent = QModelIndex()) const;

//    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

//protected:
//    QHash<int, QByteArray> roleNames() const;
//private:
//    QList<Post>group;
//    QString title;
//};

#endif // POST_H
