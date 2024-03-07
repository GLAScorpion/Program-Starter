#ifndef SCROLLEDIT_H
#define SCROLLEDIT_H

#include <QQuickItem>

class ScrollEdit : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    ScrollEdit(QQuickItem* parent = nullptr);

signals:
};

#endif // SCROLLEDIT_H
