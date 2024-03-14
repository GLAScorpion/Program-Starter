#include "buttonedit.h"

ButtonEdit::ButtonEdit(int btn_num, QString cmd,QWidget *parent)
    : QWidget{parent},layout{new QHBoxLayout()}
{
    setLayout(layout);
    layout->setSpacing(50);
    setFixedHeight(40);

}
