#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QScrollArea>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QErrorMessage>
#include "config.h"
#include "buttonedit.h"

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
    QPushButton* new_button;
    QLineEdit* conf_path_edit;
    Config* conf;
    QVBoxLayout* scroll_layout;
    QVBoxLayout* main_vert_layout;
    QErrorMessage* err_mex;
    int baud_rate = 9600;
    QString port = "COM4";
    std::map<int, ButtonEdit*> buttons;
    void add_button(int index, QString cmd = "");
public slots:
    void conf_loader();
    void populate(int baud_rate, QString port, std::map<int,QString> buttons);
    void prep_button();
    void remove_button(int index);
    void save();
    void baud_rate_edit();
    void port_edit();

};
#endif // MAINWINDOW_H
