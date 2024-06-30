import sqlite3
import os
from PyQt6.QtCore import QObject, pyqtSignal, QDateTime

class TaskManager(QObject):
    tasksChanged = pyqtSignal()

    def __init__(self, db_path="~/.tooodo/db/tooodo.db", parent=None):
        super().__init__(parent)
        self.db_path = os.path.expanduser(db_path)
        self.ensure_directory_exists()
        self.create_tasks_table()

    def ensure_directory_exists(self):
        directory = os.path.dirname(self.db_path)
        if not os.path.exists(directory):
            os.makedirs(directory, exist_ok=True)

    def create_tasks_table(self):
        conn = sqlite3.connect(self.db_path)
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS tooodo (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                title TEXT NOT NULL,
                description TEXT,
                due_date DATETIME,
                priority INT,
                completed BOOL
            )
        ''')
        conn.commit()
        conn.close()

    def add_task(self, title, description, due_date):
        conn = sqlite3.connect(self.db_path)
        cursor = conn.cursor()

        cursor.execute('''
            INSERT INTO tooodo (title, description, due_date) VALUES (?, ?, ?)
        ''', (title, description, due_date.toString("yyyy-MM-dd HH:mm:ss")))
        conn.commit()
        conn.close()
        self.tasksChanged.emit()

    def get_tasks(self):
        conn = sqlite3.connect(self.db_path)
        cursor = conn.cursor()
        cursor.execute('SELECT * FROM tooodo')
        tasks = cursor.fetchall()
        conn.close()
        return tasks

    def complete_task(self, task_id):
        self.update_task(task_id, {"completed": 1})

    def update_task(self, task_id, data):
        update_str = ", ".join(["{0} = ?".format(k) for k in data])

        values = list(data.values())
        values.append(task_id)

        if not update_str:
            return

        conn = sqlite3.connect(self.db_path)
        cursor = conn.cursor()
        cursor.execute(f'UPDATE tooodo SET {update_str} WHERE id = ?', values)
        conn.commit()
        conn.close()
        self.tasksChanged.emit()
