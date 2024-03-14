#ifndef BUTTONEDIT_H
#define BUTTONEDIT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
class ButtonEdit : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonEdit(int btn_num, QString cmd,QWidget *parent = nullptr);
private:
    QHBoxLayout* layout;
    QLineEdit* cmd_edit;
    QLabel* btn_label;
    QPushButton* btn_remove;
signals:
};

#endif // BUTTONEDIT_H
