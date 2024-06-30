import sys
from PyQt6.QtWidgets import QApplication
from quickadd import QuickAddDialog
from mainwindow import MainWindow
from trayicon import TrayIcon
from taskmanager import TaskManager

def main(mode=0):
    app = QApplication(sys.argv)
    task_manager = TaskManager()

    if mode == 1:
        quick_add_dialog = QuickAddDialog(task_manager, True)
    elif mode == 2:
        tray_icon = TrayIcon(task_manager, None)
    else:
        main_window = MainWindow(task_manager)
        main_window.show()


    sys.exit(app.exec())

if __name__ == '__main__':
    if len(sys.argv) > 1:
        if sys.argv[1] == 'tray-icon':
            main(2) #trayicon mode
        else:
            main(1) #quick-add-dialog mode
    else:
        main(0) #main app mode
