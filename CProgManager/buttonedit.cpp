#include "buttonedit.h"
#include <QMessageBox>

ButtonEdit::ButtonEdit(int btn_num, QString cmd,QWidget *parent)
    : QWidget{parent},index{btn_num},set_cmd(cmd),layout{new QHBoxLayout(this)}
{
    layout->setSpacing(ButtonEditConst::Spacing);
    layout->setAlignment(Qt::AlignVCenter);
    setFixedHeight(ButtonEditConst::Height);
    btn_label = new QLabel(QString("Button nr ") + QString::number(btn_num),this);
    btn_label->setFixedHeight(ButtonEditConst::ContentHeight);
    btn_label->setMinimumWidth(ButtonEditConst::MinWidth);
    layout->addWidget(btn_label);
    cmd_edit = new QLineEdit(cmd,this);
    cmd_edit->setFixedHeight(ButtonEditConst::ContentHeight);
    cmd_edit->setMinimumWidth(ButtonEditConst::MinBigWidth);
    cmd_edit->setReadOnly(true);
    layout->addWidget(cmd_edit);
    btn_edit = new QPushButton(QString("Edit"),this);
    btn_edit->setFixedHeight(ButtonEditConst::ContentHeight);
    btn_edit->setMinimumWidth(ButtonEditConst::MinWidth);
    layout->addWidget(btn_edit);
    btn_remove = new QPushButton(QString("Remove"),this);
    btn_remove->setFixedHeight(ButtonEditConst::ContentHeight);
    btn_remove->setMinimumWidth(ButtonEditConst::MinWidth);
    layout->addWidget(btn_remove);
    btn_confirm = new QPushButton(QString("Confirm"),this);
    btn_confirm->setFixedHeight(ButtonEditConst::ContentHeight);
    btn_confirm->setMinimumWidth(ButtonEditConst::MinWidth);
    layout->addWidget(btn_confirm);
    btn_confirm->hide();
    connect(btn_edit,&QPushButton::pressed,this,&ButtonEdit::edit_toggle);
    connect(btn_remove,&QPushButton::pressed,this,&ButtonEdit::remove_process);
    connect(btn_confirm,&QPushButton::pressed,this,&ButtonEdit::save);
    connect(cmd_edit,&QLineEdit::returnPressed,this,&ButtonEdit::save);
}

void ButtonEdit::edit_toggle(){
    if(cmd_edit->isReadOnly()){
        cmd_edit->setReadOnly(false);
        btn_edit->setText(QString("Cancel"));
        btn_remove->hide();
        btn_confirm->show();
    }else{
        cmd_edit->setReadOnly(true);
        cmd_edit->setText(set_cmd);
        btn_edit->setText(QString("Edit"));
        btn_confirm->hide();
        btn_remove->show();

    }
}

void ButtonEdit::save(){
    set_cmd = cmd_edit->text();
    cmd_edit->setReadOnly(true);
    btn_edit->setText(QString("Edit"));
    btn_confirm->hide();
    btn_remove->show();
}

void ButtonEdit::remove_process(){
    QMessageBox msgBox(this);
    msgBox.setText("Are you sure you want to remove it?");
    //msgBox.setInformativeText("");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setIcon(QMessageBox::Question);
    if(msgBox.exec() == QMessageBox::Save){
       emit remove_confirm(index);
    }
}
