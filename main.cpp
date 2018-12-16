#include "mainwindow.h"
#include "global.h"
#include <QApplication>

User *user = NULL;
QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
extern map<QString, Base> userGroup;

map<QString, Base>& operator<<(map<QString, Base>&group, QSqlDatabase db)
{
    QSqlQuery query(db);
    query.exec("select * from user");
    while(query.next())
    {
        QString id = query.value(0).toString();
        QString pwd = query.value(1).toString();
        QString username = query.value(2).toString();
        int type = query.value(3).toInt();
        if(type==HOST_USER)
        {
            int plateId = query.value(4).toInt();
            userGroup[id] = Base(id, pwd, username, type, plateId);
        }
        else
        {
            userGroup[id] = Base(id, pwd, username, type);
        }

    }
    return group;
}

int main(int argc, char *argv[])
{
    QTextCodec::codecForName("UTF-8");
    QApplication a(argc, argv);
    a.addLibraryPath("./plugins");
    //初始化数据库实例
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("foxforum");
    db.setUserName("root");
    if(!db.open())
    {
        QMessageBox::warning(0,QObject::tr("database connect error"),QObject::tr("please check your internet connect and database"));
        exit(0);
    }
    else
    {
        qDebug()<<"db connected"<<endl;
        userGroup<<db;
    }


    user = new User();
    user->Login();

    if(user->loginView->exec()==QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
}
