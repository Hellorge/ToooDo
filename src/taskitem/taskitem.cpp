#include "taskitem.h"
#include "ui_taskitem.h"
#include "libs/relativedates.h"
#include <QPushButton>
#include <QDebug>

QX_REGISTER_CPP(TaskItem)

namespace qx {
    template <> void register_class(QxClass<TaskItem> &t)
    {
        t.id(&TaskItem::id, "id");
        t.data(&TaskItem::title, "title");
        t.data(&TaskItem::description, "description");
        t.data(&TaskItem::dueDate, "due_date");
        t.data(&TaskItem::priority, "priority");
        t.data(&TaskItem::completed, "completed");
    }
}

TaskItem::TaskItem()
    : QWidget(), ui(new Ui::TaskItem), isExpanded(false)
{
    ui->setupUi(this);
    qDebug() << id << title << description;

    connect(ui->titleEdit, &QLineEdit::textChanged, this, &TaskItem::onTitleChange);
    connect(ui->descriptionEdit, &QTextEdit::textChanged, this, &TaskItem::onDescriptionChange);
    // connect(ui->titleArea, &QPushButton::clicked, this, &TaskItem::toggleDetails);
}

TaskItem::~TaskItem()
{
    delete ui;
}

QWidget *TaskItem::getUIWidget()
{
    return this;
}

void TaskItem::toggleDetails()
{
    isExpanded = !isExpanded;
    // ui->expandedLayout->setVisible(isExpanded);
    // ui->expandButton->setText(isExpanded ? "▲" : "▼");
}

void TaskItem::updateTask(const QVariantMap& data)
{
    for (auto it = data.constBegin(); it != data.constEnd(); ++it) {
        if (it.key() == "title")
            title = it.value().toString();
        else if (it.key() == "description")
            description = it.value().toString();
        else if (it.key() == "due_date")
            dueDate = it.value().toDateTime();
        else if (it.key() == "priority")
            priority = it.value().toInt();
        else if (it.key() == "completed")
            completed = it.value().toBool();
    }

    qx::dao::save(*this);
}

void TaskItem::onTitleChange(const QString &text)
{
    if (title != text) {
        title = text;
        emit dataChanged();
        // qx::dao::save(*this);
    }
}

void TaskItem::onDescriptionChange()
{
    QString text = ui->descriptionEdit->toPlainText();
    if (description != text) {
        description = text;
        emit dataChanged();
        // qx::dao::save(*this);
    }
}
