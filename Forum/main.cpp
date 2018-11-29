#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QQuickView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    QQuickView view;
//    view.setSource(QUrl("qrc:/qml/qml/Plate.qml"));
//    view.show();

    Login login_window;

    if(login_window.exec()==QDialog::Accepted){
         MainWindow w;
         w.show();
         return a.exec();
    }

    return a.exec();
}
