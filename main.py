import sys
from PyQt6.QtWidgets import QApplication
from PyQt6.QtGui import QIcon
from src.quickadd import QuickAddDialog
from src.mainwindow import MainWindow
from src.trayicon import TrayIcon
from src.taskmanager import TaskManager

def main(argv):
    app = QApplication(sys.argv)
    # app.setWindowIcon(QIcon("/run/media/hellorge/PIT/Desktop/projects/ToooDo/icons/todo.png"))
    app.setDesktopFileName('/run/media/hellorge/PIT/Desktop/projects/ToooDo/tooodo')
    task_manager = TaskManager()

    if list(set(["q", "quick-add", "quick", "quickadd", "quick add"]) & set(argv)):
        quick_add_dialog = QuickAddDialog(task_manager)
        quick_add_dialog.show()

    # elif list(set(["q", "quick-add", "quick", "quickadd", "quick add"]) & set(argv)):
    #     tray_icon = TrayIcon(task_manager, None)
    else:
        main_window = MainWindow(task_manager)
        main_window.show()

    sys.exit(app.exec())

if __name__ == '__main__':
    main(sys.argv)