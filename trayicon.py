from PyQt6.QtWidgets import QSystemTrayIcon, QApplication
from PyQt6.QtGui import QIcon
from traymenu import TrayMenu
from quickadd import QuickAddDialog

class TrayIcon(QSystemTrayIcon):
    def __init__(self, task_manager, main_window=None, parent=None):
        super().__init__(parent)
        self.task_manager = task_manager
        self.main_window = main_window

        # self.setIcon(QIcon("icons/tasks.svg"))
        self.setVisible(True)

        # self.menu = TrayMenu()

        # Connect buttons
        # self.menu.addTaskButton.clicked.connect(self.show_quick_add_dialog)
        # self.menu.exitButton.clicked.connect(QApplication.instance().quit)
        # self.setContextMenu(self.menu)

    def show_quick_add_dialog(self):
        dialog = QuickAddDialog()
        dialog.exec()
        dialog.taskAdded.connect(self.task_manager.add_task)

    def show_main_window(self):
        if self.main_window:
            self.main_window.show()
