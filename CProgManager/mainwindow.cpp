#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , conf(new Config())
    , err_mex(new QErrorMessage)
{
    ui->setupUi(this);
    scroll_area = findChild<QScrollArea*>("scroll_area");
    scroll_layout = new QVBoxLayout();
    scroll_layout->setAlignment(Qt::AlignTop);
    scroll_area->findChild<QWidget*>("scroll_area_widget_content")->setLayout(scroll_layout);
    save_button = findChild<QPushButton*>("save_button");
    load_button = findChild<QPushButton*>("load_button");
    conf_path_edit = findChild<QLineEdit*>("conf_path_edit");
    new_button = findChild<QPushButton*>("new_button");
    connect(load_button,&QPushButton::pressed,this,&MainWindow::conf_loader);
    connect(conf,&Config::content_ready,this,&MainWindow::populate);
    connect(new_button,&QPushButton::pressed,this,&MainWindow::prep_button);
    connect(save_button,&QPushButton::pressed,this,&MainWindow::save);
    connect(findChild<QAction*>("actionBaud_Rate"),&QAction::triggered,this,&MainWindow::baud_rate_edit);
    connect(findChild<QAction*>("actionPort"),&QAction::triggered,this,&MainWindow::port_edit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::conf_loader(){
    conf->SetFile(conf_path_edit->text());
    conf->xml_read();
}

void MainWindow::populate(int baud_rate, QString port, std::map<int,QString> buttons){
    this->baud_rate = baud_rate;
    this->port = port;
    for(auto i = buttons.begin(); i != buttons.end(); i++){
        add_button(i->first,i->second);
    }
}

void MainWindow::add_button(int index, QString cmd){
    buttons[index] = new ButtonEdit(index,cmd,this);
    auto btn = buttons.upper_bound(index);
    if(btn != buttons.end()){
        int i = scroll_layout->indexOf(btn->second);
        scroll_layout->insertWidget(i,buttons[index]);
    }else{
        scroll_layout->addWidget(buttons[index]);
    }
    connect(buttons[index],&ButtonEdit::remove_confirm,this,&MainWindow::remove_button);
}

void MainWindow::prep_button(){
    bool ok;
    int index = QInputDialog::getInt(this, tr("Add a new button"),tr("New button number:"),0,0,INT_MAX,1, &ok);
    if (ok){
        if(buttons[index]){
            err_mex->showMessage("Button already registered");
        }else{
            add_button(index);
        }
    }
}

void MainWindow::remove_button(int index){
    ButtonEdit* btn = buttons.extract(index).mapped();
    scroll_layout->removeWidget(btn);
    disconnect(btn,&ButtonEdit::remove_confirm,this,&MainWindow::remove_button);
    btn->deleteLater();
}

void MainWindow::save(){
    std::map<int,QString> btns;
    for(auto i = buttons.begin(); i != buttons.end(); i++){
        btns[i->first] = i->second->GetCmd();
    }
    conf->SetFile(conf_path_edit->text());
    conf->xml_write(baud_rate,port,btns);
}
void MainWindow::baud_rate_edit(){
    bool ok;
    int rate = QInputDialog::getInt(this, tr("Change baud rate"),tr("Baud rate:"),baud_rate,0,INT_MAX,1, &ok);
    if (ok){
        baud_rate = rate;
    }
}

void MainWindow::port_edit(){
    bool ok;
    QString text = QInputDialog::getText(this, tr("Change serial port"),tr("Serial port:"), QLineEdit::Normal,port, &ok);
    if (ok && !text.isEmpty()) port = text;
}
