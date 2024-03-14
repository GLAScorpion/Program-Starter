#include "config.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QRegularExpression>
#include <QFile>
Config::Config(QString filename, QObject *parent)
    :QObject(parent),file{filename}
{
    bool exist = QFile(file).exists();
    if (!exist){
        xml_write();
    }else{
        xml_read();
    }
}


void Config::xml_write(){
    QFile* open_file = new QFile(file);
    open_file->open(QFile::ReadWrite);
    QXmlStreamWriter* xml_writer = new QXmlStreamWriter(open_file);
    xml_writer->setAutoFormatting(true);
    xml_writer->writeStartDocument();
    xml_writer->writeStartElement("config");
    xml_writer->writeStartElement("buttons");
    for(auto i = buttons.begin();i != buttons.end();i++){
        xml_writer->writeStartElement("button_" + std::to_string(i->first));
        xml_writer->writeCharacters(i->second);
        xml_writer->writeEndElement();
    }
    xml_writer->writeEndElement();
    xml_writer->writeEmptyElement("port");
    xml_writer->writeAttribute("port", port);
    xml_writer->writeAttribute("baud_rate", std::to_string(baud_rate));
    xml_writer->writeEndElement();
    xml_writer->writeEndDocument();
    open_file->close();
}

void Config::xml_read(){
    QFile* open_file = new QFile(file);
    open_file->open(QFile::ReadWrite);
    QXmlStreamReader* xml_reader = new QXmlStreamReader(open_file);
    while(!xml_reader->atEnd()){
        QXmlStreamReader::TokenType type = xml_reader->readNext();
        if(type == QXmlStreamReader::StartElement){
            if(xml_reader->name().toString() == "buttons"){
                while(xml_reader->readNextStartElement()){
                    QString tkn = xml_reader->name().toString();
                    buttons[button_indexer(tkn)] = xml_reader->readElementText();
                }
            }
            if(xml_reader->name().toString() == "port"){
                QXmlStreamAttributes attr = xml_reader->attributes();
                port = attr.value("port").toString();
                baud_rate = attr.value("baud_rate").toInt();

            }
        }
    }
    open_file->close();
}

int Config::button_indexer(QString btn){
    static QRegularExpression btn_pattern("button_([0-9])");
    QRegularExpressionMatch match = btn_pattern.match(btn);
    return match.captured(1).toInt();
}
