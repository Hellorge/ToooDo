#include "taskmanager.h"
#include "taskitem/taskitem.h"
#include <QDir>
#include <QxOrm.h>
#include <QSqlDatabase>
#include <QSqlQuery>

TaskManager::TaskManager(QObject *parent)
    : QObject(parent)
{
    db_path = QDir::homePath() + "/.tooodo/db";
    ensureDirectoryExists();
    createTasksTable();
    // printTableSchema();
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

void TaskManager::updateTask(TaskItem *task)
{
    qx::dao::save(task);
    emit tasksChanged();
}

QList<TaskItem*> TaskManager::getTasks()
{
    QList<TaskItem*> taskList;
    qx::dao::fetch_all(taskList);
    return taskList;
}

void TaskManager::printTableSchema()
{
    QString db_file = db_path + "/tooodo.db";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "schema_connection");
    db.setDatabaseName(db_file);

    if (!db.open())
    {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return;
    }

    QString tableName = "TaskItem";
    QSqlQuery query(db);
    if (query.exec("SELECT * from " + tableName + ";"))
    {
        while (query.next())
       {
           int id = query.value("id").toInt();
           QString title = query.value("title").toString();
           QString description = query.value("description").toString();
           QDateTime dueDate = query.value("due_date").toDateTime();
           int priority = query.value("priority").toInt();
           bool completed = query.value("completed").toBool();

           qDebug() << "ID:" << id
                    << "Title:" << title;
       }
    }
    else
    {
        qDebug() << "Failed to retrieve table schema:" << query.lastError().text();
    }

    db.close();
}
