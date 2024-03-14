#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scroll_area = findChild<QScrollArea*>("scroll_area");
    save_button = findChild<QPushButton*>("save_button");
    load_button = findChild<QPushButton*>("load_button");
    conf_path_edit = findChild<QLineEdit*>("conf_path_edit");
    connect(load_button,&QPushButton::pressed,this,&MainWindow::conf_loader);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::conf_loader(){
    QString file_name = conf_path_edit->text();
    conf = new Config(file_name);
}
