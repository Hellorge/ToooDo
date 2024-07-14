#include "taskmanager.h"
#include "taskitem/taskitem.h"
#include <QDir>
#include <QxOrm.h>

TaskManager::TaskManager(QObject *parent)
    : QObject(parent)
{
    db_path = QDir::homePath() + "/.tooodo/db";
    ensureDirectoryExists();
    createTasksTable();
}

void TaskManager::ensureDirectoryExists()
{
    QDir dir(db_path);

    if (!dir.exists()) {
        dir.mkpath(".");
    }
}

void TaskManager::createTasksTable()
{
    QString db_file = db_path + "/tooodo.db";

    qx::QxSqlDatabase::getSingleton()->setDriverName("QSQLITE");
    qx::QxSqlDatabase::getSingleton()->setDatabaseName(db_file);
    qx::QxSqlDatabase::getSingleton()->getDatabase();

    qx::dao::create_table<TaskItem>();
}

void TaskManager::addTask(TaskItem *task)
{
    qx::dao::insert(task);

    emit tasksChanged();
}

QList<QSharedPointer<TaskItem>> TaskManager::getTasks()
{
    QList<QSharedPointer<TaskItem>> taskList;
    qx::dao::fetch_all(taskList);
    return taskList;
}

void TaskManager::completeTask(int taskId)
{
    updateTask(taskId, {{"completed", 1}});
}

void TaskManager::updateTask(int taskId, const QVariantMap& data)
{
    // TaskItem task;
    // task.id = taskId;
    // qx::dao::fetch_by_id(task);

    // task.updateTask(data);

    emit tasksChanged();
}
