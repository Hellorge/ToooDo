from PyQt6.QtWidgets import QMainWindow, QPushButton, QVBoxLayout, QWidget, QListWidget, QListWidgetItem, QHBoxLayout
from taskitem import TaskItemWidget

class MainWindow(QMainWindow):
    def __init__(self, task_manager, parent=None):
        super().__init__(parent)
        self.task_manager = task_manager

        self.setWindowTitle("ToooDo")
        self.setGeometry(100, 100, 600, 400)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)

        self.layout = QHBoxLayout(self.central_widget)

        # List widget to display tasks
        self.task_list = QListWidget(self)
        self.layout.addWidget(self.task_list)

        # Refresh button
        self.refresh_button = QPushButton("Refresh", self)
        self.refresh_button.clicked.connect(self.fetch_tasks)
        self.layout.addWidget(self.refresh_button)

        # Fetch and display tasks initially
        self.fetch_tasks()

    def fetch_tasks(self):
        self.task_list.clear()
        tasks = self.task_manager.get_tasks()
        for task in tasks:
            item = QListWidgetItem(self.task_list)
            task_widget = TaskItemWidget(task)
            item.setSizeHint(task_widget.sizeHint())
            self.task_list.addItem(item)
            self.task_list.setItemWidget(item, task_widget)

        print(f"Fetched tasks: {tasks}")
