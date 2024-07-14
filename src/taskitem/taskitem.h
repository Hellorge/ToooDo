#ifndef TASKITEM_H
#define TASKITEM_H

// #include <QWidget>
// #include <QVariantMap>
// #include <QString>
#include <QWidget>
#include <QMouseEvent>
#include <QxOrm.h>

namespace Ui {
    class TaskItem;
}

class TaskItem : public QWidget
{
    Q_OBJECT
    QX_REGISTER_FRIEND_CLASS(TaskItem)

public:
    explicit TaskItem();
    ~TaskItem();

    QWidget *getUIWidget();
    Ui::TaskItem *ui;

private:

    long id;
    QString title;
    QString description;
    QDateTime dueDate;
    int priority;
    bool completed;

    bool isExpanded;

    void updateTask(const QVariantMap &data);

private slots:
    void toggleDetails();
    void onDescriptionChange();
    void onTitleChange(const QString &text);

signals:
    void dataChanged();

};

QX_REGISTER_HPP(TaskItem, qx::trait::no_base_class_defined, 1)

#endif // TASKITEM_H
