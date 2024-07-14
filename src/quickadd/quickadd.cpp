#include <QPushButton>
#include <QMessageBox>
#include "quickadd.h"
#include "ui_quickadd.h"
#include "taskitem/taskitem.h"
// #include "svgmanager/svgmanager.h"

QuickAdd::QuickAdd(TaskManager *taskManager, QWidget *parent) :
    QDialog(parent),
    taskManager(taskManager),
    ui(new Ui::QuickAdd),
    task(new TaskItem())
{
    ui->setupUi(this);
    task->setMode(1);
    ui->newTaskBox->addWidget(task);
    connect(ui->buttonBox->button(QDialogButtonBox::Save), &QPushButton::pressed, this, &QuickAdd::addTask);

    // QString svgPath = "/run/media/hellorge/PIT/Desktop/projects/pycreator/ToooDo/icons/svgs/flag-outline.svg";
    // SvgIconManager svgIconManager;
    // svgIconManager.addButton(ui->priorityButton, svgPath);
}

void QuickAdd::addTask()
{
    if (!task->validate()) {
        QMessageBox::warning(this, "Warning", "Title cannot be empty.");
        return;
    }

    taskManager->addTask(task);

    this->close();
}

QuickAdd::~QuickAdd()
{
    delete ui;
}
