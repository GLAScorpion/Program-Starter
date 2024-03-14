#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QScrollArea>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include "config.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QScrollArea* scroll_area;
    QPushButton* save_button;
    QPushButton* load_button;
    QLineEdit* conf_path_edit;
    Config* conf;
public slots:
    void conf_loader();
};
#endif // MAINWINDOW_H
