#include "mainwindow.h"
#include "login.h"
#include "user.h"
#include "header.h"
#include <QApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Login login_window(&user);
    if(login_window.exec()==QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }

}
