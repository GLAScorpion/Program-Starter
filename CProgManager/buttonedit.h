#ifndef BUTTONEDIT_H
#define BUTTONEDIT_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

enum ButtonEditConst : int {
    Spacing = 50, Height = 40, MinWidth = 100, MinBigWidth = 300, ContentHeight = 30
};

class ButtonEdit : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonEdit(int btn_num, QString cmd,QWidget *parent = nullptr);
    int GetIndex(){return index;}
    QString GetCmd(){return set_cmd;}
private:
    int index;
    QString set_cmd;
    QHBoxLayout* layout;
    QLineEdit* cmd_edit;
    QLabel* btn_label;
    QPushButton* btn_edit;
    QPushButton* btn_remove;
    QPushButton* btn_confirm;
public slots:
    void edit_toggle();
    void remove_process();
    void save();
signals:
    void remove_confirm(int index);
};

#endif // BUTTONEDIT_H
