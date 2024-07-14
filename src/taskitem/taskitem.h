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
    long id;
    QString title;
    QString description;
    QDateTime dueDate;
    int priority;
    bool completed;

    bool validate();
    void setCompactMode(bool compact);
    int mode() const;
    void setMode(int mode);
    void bindData();

private:
    Ui::TaskItem *ui;

    bool isCompactMode;
    QPropertyAnimation *animation;

private slots:
    void onTitleChanged(const QString &text);
    void onDescriptionChanged();
    void onDueDateChanged(const QDateTime &date);
    void onPriorityChanged(int &value);
    void onCompletedChanged(bool &checked);
    void update();

signals:
    void dataChanged();

};

QX_REGISTER_HPP(TaskItem, qx::trait::no_base_class_defined, 0)

namespace qx {
namespace dao {
namespace detail {

template <>
struct QxDao_Trigger<TaskItem>
{
    static inline void onBeforeInsert(TaskItem *t, qx::dao::detail::IxDao_Helper *dao)
    { Q_UNUSED(t); Q_UNUSED(dao); }
    static inline void onBeforeUpdate(TaskItem *t, qx::dao::detail::IxDao_Helper *dao)
    { Q_UNUSED(t); Q_UNUSED(dao); }
    static inline void onBeforeDelete(TaskItem *t, qx::dao::detail::IxDao_Helper *dao)
    { Q_UNUSED(t); Q_UNUSED(dao); }
    static inline void onBeforeFetch(TaskItem *t, qx::dao::detail::IxDao_Helper *dao)
    { Q_UNUSED(t); Q_UNUSED(dao); }
    static inline void onAfterInsert(TaskItem *t, qx::dao::detail::IxDao_Helper *dao)
    { Q_UNUSED(t); Q_UNUSED(dao); }
    static inline void onAfterUpdate(TaskItem *t, qx::dao::detail::IxDao_Helper *dao)
    { Q_UNUSED(t); Q_UNUSED(dao); }
    static inline void onAfterDelete(TaskItem *t, qx::dao::detail::IxDao_Helper *dao)
    { Q_UNUSED(t); Q_UNUSED(dao); }
    static inline void onAfterFetch(TaskItem *t, qx::dao::detail::IxDao_Helper *dao)
    {
        if (t) { t->bindData(); }
        Q_UNUSED(dao);
    }
};

} // namespace detail
} // namespace dao
} // namespace qx


#endif // TASKITEM_H
