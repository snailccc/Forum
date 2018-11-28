#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login login_window;

    if(login_window.exec()==QDialog::Accepted){
         MainWindow w;
         w.show();
         return a.exec();
    }

    return a.exec();
}
