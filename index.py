import sys
from PyQt6.QtWidgets import QApplication, QMainWindow, QLabel, QVBoxLayout, QWidget
from PyQt6.QtGui import QKeySequence, QClipboard

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle("System-wide Text Selection Example")
        self.setGeometry(100, 100, 400, 300)

        # Label to display selected text
        self.selected_text_label = QLabel("Selected Text: ")
        self.statusBar().addPermanentWidget(self.selected_text_label)

        # Monitor clipboard changes
        clipboard = QApplication.clipboard()
        clipboard.dataChanged.connect(self.onClipboardChanged)

        # Create a global shortcut Ctrl+Shift+C
        # shortcut = QShortcut(QKeySequence("Ctrl+Shift+C"), self)
        # shortcut.activated.connect(self.onShortcutActivated)

    def onClipboardChanged(self):
        clipboard = QApplication.clipboard()
        selected_text = clipboard.text(mode=QClipboard.Mode.Selection)
        self.selected_text_label.setText(f"Selected Text: {selected_text}")

    def onShortcutActivated(self):
        clipboard = QApplication.clipboard()
        selected_text = clipboard.text(mode=QClipboard.Mode.Selection)
        if selected_text:
            # Do something with the selected text
            print(f"Selected text (from shortcut): {selected_text}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec())
