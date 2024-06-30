from PyQt6.QtWidgets import QMenu, QPushButton, QVBoxLayout
from PyQt6.QtGui import QIcon

class TrayMenu(QMenu):
    def __init__(self, parent=None):
        super().__init__(parent)

        # Create buttons
        self.addTaskButton = QPushButton("New", self)
        self.addTaskButton.setShortcut("Ctrl+N")

        self.exitButton = QPushButton("Exit", self)
        self.exitButton.setShortcut("Ctrl+Q")

        self.showMainWindowButton = QPushButton("Open", self)
        self.showMainWindowButton.setShortcut("Ctrl+O")

    def onAddTaskClicked(self):
        # Emit a signal or call a method to handle "Add Task" button click
        # Example: self.addTaskButtonClicked.emit()
        pass
