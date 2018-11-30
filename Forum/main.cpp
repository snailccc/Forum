#include "mainwindow.h"
#include "login.h"
#include "user.h"
#include "header.h"
#include <QApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    while(1)
    {
        User *user = NULL;
        Login login_window(&user);

        if(login_window.exec()==QDialog::Accepted){
             MainWindow w(0,user);
             w.show();
             return a.exec();
        }
    }

    return a.exec();

}
