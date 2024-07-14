#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taskmanager/taskmanager.h"
#include "quickadd/quickadd.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(TaskManager* taskManager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void fetchTasks();
    void addTask();

private:
    Ui::MainWindow *ui;
    QuickAdd* quickAdd;
    TaskManager* taskManager;
};

#endif // MAINWINDOW_H
