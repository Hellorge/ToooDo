#ifndef TASKITEM_H
#define TASKITEM_H

#include <QWidget>
#include <QMouseEvent>
#include <QxOrm.h>
#include <QPropertyAnimation>

namespace Ui {
    class TaskItem;
}

class TaskItem : public QWidget
{
    Q_OBJECT
    QX_REGISTER_FRIEND_CLASS(TaskItem)
    Q_PROPERTY(int mode READ mode WRITE setMode)

public:
    explicit TaskItem(QWidget *parent = nullptr);
    ~TaskItem();

    QList<QString> validate_messages;

    bool validate();
    void setCompactMode(bool compact);
    int mode() const;
    void setMode(int mode);

private:
    Ui::TaskItem *ui;

    long id;
    QString title;
    QString description;
    QDateTime dueDate;
    int priority;
    bool completed;

    bool isCompactMode;
    QPropertyAnimation *animation;

private slots:
    void onTitleChanged(const QString &text);
    void onDescriptionChanged();
    void onDueDateChanged(const QDateTime &date);
    void onPriorityChanged(int &value);
    void onCompletedChanged(bool &checked);
    void bindData();
    void update();

signals:
    void dataChanged();

};

QX_REGISTER_HPP(TaskItem, qx::trait::no_base_class_defined, 0)

#endif // TASKITEM_H
