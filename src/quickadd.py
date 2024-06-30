from PyQt6.QtWidgets import QDialog, QLineEdit, QTextEdit, QPushButton, QVBoxLayout, QHBoxLayout, QDateTimeEdit
from PyQt6.QtCore import pyqtSignal, QDateTime
# from PyQt6.QtGui import QIcon

class QuickAddDialog(QDialog):
    taskAdded = pyqtSignal(str, str, QDateTime)

    def __init__(self, task_manager, parent=None):
        super().__init__(parent)

        self.task_manager = task_manager

        self.build()
        self.connect()

    def connect(self):
        self.taskAdded.connect(self.task_manager.add_task)

    def add_task(self):
        title = self.titleEdit.text()
        description = self.descriptionEdit.toPlainText()
        due_date = self.dueDateEdit.dateTime()
        self.taskAdded.emit(title, description, due_date)
        self.close()

    def build(self):
        self.setWindowTitle("ToooDo")
        # self.setWindowIcon(QIcon("./icons/todo.png"))
        self.setGeometry(0, 0, 416, 230)

        self.titleEdit = QLineEdit(self)
        self.titleEdit.setPlaceholderText("Title")

        self.descriptionEdit = QTextEdit(self)
        self.descriptionEdit.setPlaceholderText("Description")

        self.dueDateEdit = QDateTimeEdit(self)
        self.dueDateEdit.setCalendarPopup(True)

        self.addButton = QPushButton("Add", self)
        self.addButton.clicked.connect(self.add_task)

        self.cancelButton = QPushButton("Cancel", self)
        self.cancelButton.clicked.connect(self.close)

        # Layout for title and description
        layout = QVBoxLayout()
        layout.addWidget(self.titleEdit)
        layout.addWidget(self.descriptionEdit)

        # Horizontal layout for date and buttons
        buttonLayout = QHBoxLayout()
        buttonLayout.addWidget(self.dueDateEdit)
        buttonLayout.addStretch()
        buttonLayout.addWidget(self.addButton)
        buttonLayout.addWidget(self.cancelButton)

        # Add the horizontal layout to the main layout
        layout.addLayout(buttonLayout)
        
        self.setLayout(layout)