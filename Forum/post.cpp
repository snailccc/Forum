#include "post.h"

Post::Post(QWidget *parent, int id, QString title, QString content):
    QPushButton(parent), id(id),title(title),content(content)
{
    this->setText(title);
}





////////////////////////////////PostGroup///////////////////////////////////////////////
//PostGroup::PostGroup(QObject *parent)
//    : QAbstractListModel(parent)
//{
//}

//void PostGroup::AddPost(const Post &post)
//{
//    beginInsertRows(QModelIndex(), rowCount(), rowCount());
//    group << post;
//    endInsertRows();
//}

//int PostGroup::rowCount(const QModelIndex & parent) const {
//    Q_UNUSED(parent);
//    return group.count();
//}

//QVariant PostGroup::data(const QModelIndex & index, int role) const {
//    if (index.row() < 0 || index.row() >= group.count())
//        return QVariant();

//    const Post &post = group[index.row()];
//    if (role == TitleRole)
//        return post.Title();
//    else if (role == ContentRole)
//        return post.Content();
//    else if (role == IDRole)
//        return post.Id();
//    return QVariant();
//}

//QHash<int, QByteArray> PostGroup::roleNames() const {
//    QHash<int, QByteArray> roles;
//    roles[TitleRole] = "title";
//    roles[ContentRole] = "content";
//    roles[IDRole] = "id";
//    return roles;
//}
