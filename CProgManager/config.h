#ifndef CONFIG_H
#define CONFIG_H
#include <QObject>
#include <map>
class Config : public QObject
{
    Q_OBJECT
public:
    Config(QObject *parent = nullptr):QObject(parent){}
    void SetFile(QString filename){file = filename;}

private:
    int button_indexer(QString btn);
    QString file = "";
public slots:
    void xml_write(int baud_rate, QString port, std::map<int,QString> buttons);
    void xml_read();
signals:
    void content_ready(int baud_rate, QString port, std::map<int,QString> buttons);
};

#endif // CONFIG_H
