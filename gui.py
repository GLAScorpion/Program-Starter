import sys
from PyQt6.QtGui import QGuiApplication
from PyQt6.QtQml import QQmlApplicationEngine

class GUI:
    def __init__(self):
        app = QGuiApplication(sys.argv)
        engine = QQmlApplicationEngine()
        engine.quit.connect(app.quit)
        engine.load('main.qml')
        sys.exit(app.exec())