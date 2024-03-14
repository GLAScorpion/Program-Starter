#ifndef CONFIG_H
#define CONFIG_H
#include <QObject>
#include <map>
class Config : public QObject
{
    Q_OBJECT
public:
    Config(QString filename, QObject *parent = nullptr);
    std::map<int,QString>* btns(){return &buttons;}
    void SetPort(QString port){this->port = port;}
    void SetBaudRate(int rate){this->baud_rate = rate;}
    QString GetPort(){return port;}
    int GetBaudRate(){return baud_rate;}
    QString GetCmd(int index){return buttons[index];}
private:
    int button_indexer(QString btn);
    std::map<int,QString> buttons;
    QString file;
    QString port = "COM4";
    int baud_rate = 9600;
public slots:
    void xml_write();
    void xml_read();
};

#endif // CONFIG_H
