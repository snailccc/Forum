#ifndef POST_H
#define POST_H
#include "header.h"
#include "comment.h"
#include<QDateTime>
#include<QAbstractListModel>
#include<QStringList>
#include<QObject>
#include<QVariant>

class Post
{
private:
    QString title,content;
    int timestamp, id;

public:
    Post(int id, QString title, QString content);
    Q_INVOKABLE QString Title()const{return title;}
    Q_INVOKABLE int Id()const{return id;}
    Q_INVOKABLE QString Content()const{return content;}
};

//////////////////////////////PostGroup////////////////////////////////////////

class PostGroup:public QAbstractListModel
{
public:
    enum PostRoles {
        TitleRole = Qt::UserRole + 1,
        ContentRole,
        IDRole
    };

    PostGroup(QObject *parent = 0);

    void AddPost(const Post &post);

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Post>group;
    QString title;
};

#endif // POST_H
