#ifndef GLOBAL_H
#define GLOBAL_H

#include "user.h"
#include <map>
#include <vector>
#include <QDialog>
#include <QDebug>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QStringList>
#include <QMessageBox>
#include <QObject>
#include <QHash>
#include <QPalette>
#include <QPixmap>
#include <iostream>
using namespace std;

//extern User *user;
extern QSqlDatabase db;


#define COMMENT_USER 1
#define HOST_USER 2
#define MANAGER 3
#define ANONYMOUS 4

//网络操作
#define op_addpost 1
#define op_delpost 2
#define op_addcomment 3
#define op_delcomment 4
#define op_appoint 5
#define op_remove 6

#endif // GLOBAL_H
