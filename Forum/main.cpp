#include "mainwindow.h"
#include "login.h"
#include "user.h"
#include "header.h"
#include <QApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    user = new User("");
    user->Login();
    if(user->loginView->exec()==QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }

}
