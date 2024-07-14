#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include "taskitem/taskitem.h"

class TaskManager : public QObject
{
    Q_OBJECT

public:
    explicit TaskManager(QObject *parent = nullptr);
    void addTask(TaskItem *task);
    QList<TaskItem*> getTasks();
    void updateTask(TaskItem *task);
    void printTableSchema();

signals:
    void tasksChanged();

private:
    QString db_path;

    void ensureDirectoryExists();
    void createTasksTable();

};

#endif // TASKMANAGER_H
