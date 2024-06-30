import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QListWidget, QVBoxLayout, QHBoxLayout, QWidget, QPushButton, QLabel, QListWidgetItem, QFrame
from PyQt6.QtGui import QIcon
from PyQt6.QtCore import Qt
from taskmanager import TaskManager

class MainWindow(QMainWindow):
    def __init__(self, task_manager, parent=None):
        super().__init__(parent)
        self.task_manager = task_manager
        self.parent = parent

        self.build()
        self.fetch_tasks()
    
    def fetch_tasks(self):
        self.task_list.clear()
        tasks = self.task_manager.get_tasks()
        for task in tasks:
            item = QListWidgetItem(f"{task[1]} - {task[2]}")
            self.task_list.addItem(item)

    def build(self):
        self.setWindowTitle("ToooDo")
        self.setWindowIcon(QIcon("icons/korg-todo.png"))
        self.setGeometry(100, 100, 800, 600)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.layout = QHBoxLayout(self.central_widget)
        
        # Sidebar
        self.sidebar = QListWidget()
        self.sidebar.setFixedWidth(200)
        self.sidebar.addItem("Inbox")
        self.sidebar.addItem("Today")
        self.sidebar.addItem("Scheduled")
        self.sidebar.addItem("Labels")
        self.layout.addWidget(self.sidebar)
        
        # Main content area
        self.content_layout = QVBoxLayout()
        self.layout.addLayout(self.content_layout)
        
        # Task display
        self.task_list = QListWidget()
        self.content_layout.addWidget(self.task_list)
        
        # Refresh Button
        self.refresh_button = QPushButton("Refresh")
        self.refresh_button.clicked.connect(self.fetch_tasks)
        self.content_layout.addWidget(self.refresh_button)