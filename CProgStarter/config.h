#ifndef CONFIG_H
#define CONFIG_H
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <map>
#include <string>
class Config
{
public:
    Config(char* filename);
    void SetButton(int index, std::string cmd);
    void SetPort(std::string port);
    void SetBaudRate(int rate);
    std::string GetPort(){return port;}
    int GetBaudRate(){return baud_rate;}
private:
    void xml_write();
    int button_indexer(std::string btn);
    std::map<int,std::string> buttons;
    QFile file;
    QXmlStreamReader* xml_reader;
    QXmlStreamWriter* xml_writer;
    std::string port = "COM4";
    int baud_rate = 9600;
};

#endif // CONFIG_H
