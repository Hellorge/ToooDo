#ifndef QUICKADD_H
#define QUICKADD_H

#include <QDialog>
#include "taskmanager/taskmanager.h"
#include "taskitem/taskitem.h"

namespace Ui {
class QuickAdd;
}

class QuickAdd : public QDialog
{
    Q_OBJECT

public:
    explicit QuickAdd(TaskManager *taskManager, QWidget *parent = nullptr);
    ~QuickAdd();

private slots:
    void addTask();

private:
    Ui::QuickAdd *ui;
    TaskManager *taskManager;
    TaskItem *task;
};

#endif // QUICKADD_H
