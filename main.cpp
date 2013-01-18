#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet("QTextEdit { background-color: QColor(0, 0, 0, 220)}");
    MainWindow w;
    w.show();
    
    return a.exec();
}
