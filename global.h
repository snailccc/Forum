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

extern User *user;
extern QSqlDatabase db;


#define COMMENT_USER 1
#define HOST_USER 2
#define MANAGER 3
#define ANONYMOUS 4

#endif // GLOBAL_H
