#include "mainwindow/mainwindow.h"
#include "quickadd/quickadd.h"
#include "taskmanager/taskmanager.h"

#include <QApplication>
#include <QString>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TaskManager tm;

    if (argc > 1 && QString(argv[1]) == "-q") {
        QuickAdd d(&tm);
        d.exec();
    } else {
        MainWindow w(&tm);
        w.show();
        return a.exec();
    }
}
