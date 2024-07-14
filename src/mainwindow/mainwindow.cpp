#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskitem/taskitem.h"
#include <QListWidgetItem>
#include <QVariantMap>
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

    QList<QSharedPointer<TaskItem>> tasks = taskManager->getTasks();

    qDebug() << tasks;
    for (const auto &task : tasks) {
        QWidget *taskWidget = task->getUIWidget();

        QListWidgetItem *item = new QListWidgetItem(ui->taskList);
        item->setSizeHint(taskWidget->sizeHint());
        ui->taskList->addItem(item);
        // ui->taskList->setItemWidget(item, taskWidget);
    }
}

void MainWindow::addTask()
{
    QuickAdd quickAdd(taskManager, this);
    quickAdd.exec();

    fetchTasks();
}
