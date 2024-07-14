#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskitem/taskitem.h"
#include <QListWidgetItem>
#include <QToolButton>

MainWindow::MainWindow(TaskManager *taskManager, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), taskManager(taskManager)
{
    ui->setupUi(this);
    fetchTasks();

    // connect(ui->refreshButton, &QToolButton::clicked, this, &MainWindow::fetchTasks);
    connect(ui->addButton, &QToolButton::clicked, this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetchTasks()
{
    ui->taskList->clear();

    QList<TaskItem*> tasks = taskManager->getTasks();

    for (TaskItem *task : tasks) {
        QListWidgetItem *item = new QListWidgetItem(ui->taskList);

        task->setParent(ui->taskList);
        item->setSizeHint(task->sizeHint());
        ui->taskList->setItemWidget(item, task);
    }
}

void MainWindow::addTask()
{
    QuickAdd quickAdd(taskManager, this);
    quickAdd.exec();

    fetchTasks();
}
