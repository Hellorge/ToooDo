#include "taskitem.h"
#include "ui_taskitem.h"
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

TaskItem::TaskItem(QWidget *parent)
    : QWidget(parent), ui(new Ui::TaskItem), isCompactMode(false)
{
    ui->setupUi(this);
    bindData();

    // animation = new QPropertyAnimation(this, "geometry");
    // animation->setDuration(300);
    // animation->setEasingCurve(QEasingCurve::InOutQuad);

    setCompactMode(true);

}

TaskItem::~TaskItem()
{
    delete ui;
}

void TaskItem::bindData()
{
    ui->titleEdit->setText(title);
    ui->descriptionEdit->setPlainText(description);
    // ui->dueDateEdit->setDateTime(dueDate);
    // ui->prioritySpin->setValue(priority);
    // ui->completedCheck->setChecked(completed);

    connect(ui->titleEdit, &QLineEdit::textChanged, this, &TaskItem::onTitleChanged);
    connect(ui->descriptionEdit, &QTextEdit::textChanged, this, &TaskItem::onDescriptionChanged);
    // connect(ui->dueDateEdit, &QDateTimeEdit::dateTimeChanged, this, &TaskItem::onDueDateChanged);
    // connect(ui->prioritySpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &TaskItem::onPriorityChanged);
    // connect(ui->completedCheck, &QCheckBox::toggled, this, &TaskItem::onCompletedChanged);
}

bool TaskItem::validate()
{
    // validate_messages

    return true;
}

void TaskItem::update()
{
    qx::dao::save(*this);
    emit dataChanged();
}

int TaskItem::mode() const
{
    return isCompactMode ? 0 : 1;
}

void TaskItem::setMode(int mode)
{
    setCompactMode(mode == 0);
}

void TaskItem::setCompactMode(bool compact)
{
    if (isCompactMode == compact)
        return;

    isCompactMode = compact;

    // QRect startRect = this->geometry();
    // QRect endRect;

    if (compact) {
        // endRect = QRect(startRect.topLeft(), QSize(startRect.width(), 50)); // Adjust size for compact mode

        ui->titleEdit->setVisible(true);
        ui->descriptionEdit->setVisible(false);
        ui->propertiesBox->setVisible(false);
        // ui->dueDateEdit->setVisible(false);
        // ui->prioritySpin->setVisible(false);
        // ui->completedCheck->setVisible(true);

    } else {
        // endRect = QRect(startRect.topLeft(), QSize(startRect.width(), 200)); // Adjust size for full mode

        ui->titleEdit->setVisible(true);
        ui->descriptionEdit->setVisible(true);
        ui->propertiesBox->setVisible(true);
        // ui->dueDateEdit->setVisible(true);
        // ui->prioritySpin->setVisible(true);
        // ui->completedCheck->setVisible(true);
    }

    // animation->setStartValue(startRect);
    // animation->setEndValue(endRect);

    // animation->start();
}

void TaskItem::onTitleChanged(const QString &text)
{
    if (title != text) {
        title = text;
        update();
    }
}

void TaskItem::onDescriptionChanged()
{
    QString text = ui->descriptionEdit->toPlainText();
    if (description != text) {
        description = text;
        update();
    }
}

void TaskItem::onDueDateChanged(const QDateTime &date)
{
    if (dueDate != date) {
        dueDate = date;
        update();
    }
}

void TaskItem::onPriorityChanged(int &value)
{
    if (priority != value) {
        priority = value;
        update();
    }
}

void TaskItem::onCompletedChanged(bool &checked)
{
    if (completed != checked) {
        completed = checked;
        update();
    }
}
