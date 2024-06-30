from PyQt6.QtWidgets import QWidget, QVBoxLayout, QLabel, QHBoxLayout, QPushButton
from PyQt6.QtCore import QDateTime

class TaskItemWidget(QWidget):
    def __init__(self, task, parent=None):
        super().__init__(parent)
        self.task = task

        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        # Title and due date
        title_layout = QHBoxLayout()
        title_label = QLabel(f"Title: {self.task[1]}")
        title_label.setStyleSheet("font-weight: bold; font-size: 14px;")
        due_date_label = QLabel(f"Due Date: {self.task[3]}")
        due_date_label.setStyleSheet("color: grey; font-size: 12px;")
        title_layout.addWidget(title_label)
        title_layout.addWidget(due_date_label)
        
        # Description
        description_label = QLabel(f"Description: {self.task[2]}")
        description_label.setWordWrap(True)
        
        # Completed status
        completed_label = QLabel(f"Completed: {'Yes' if self.task[5] else 'No'}")
        completed_label.setStyleSheet("color: green;" if self.task[5] else "color: red;")
        
        layout.addLayout(title_layout)
        layout.addWidget(description_label)
        layout.addWidget(completed_label)
        
        self.setLayout(layout)
