#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QObject>
#include <QVariantMap>
#include <QVariantList>
#include <QDateTime>
#include "taskitem/taskitem.h"

class TaskManager : public QObject
{
    Q_OBJECT

public:
    explicit TaskManager(QObject *parent = nullptr);
    void addTask(TaskItem *task);
    QList<QSharedPointer<TaskItem>> getTasks();
    void completeTask(int taskId);
    void updateTask(int taskId, const QMap<QString, QVariant> &data);

signals:
    void tasksChanged();

private:
    QString db_path;

    void ensureDirectoryExists();
    void createTasksTable();

};

#endif // TASKMANAGER_H
