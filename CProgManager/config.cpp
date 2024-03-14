#include "config.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QRegularExpression>
#include <QFile>

void Config::xml_write(int baud_rate, QString port, std::map<int,QString> buttons){
    QFile open_file = QFile(file);
    open_file.open(QFile::ReadWrite);
    QXmlStreamWriter xml_writer(&open_file);
    xml_writer.setAutoFormatting(true);
    xml_writer.writeStartDocument();
    xml_writer.writeStartElement("config");
    xml_writer.writeStartElement("buttons");
    for(auto i = buttons.begin();i != buttons.end();i++){
        xml_writer.writeStartElement(QString("button_") + QString::number(i->first));
        xml_writer.writeCharacters(i->second);
        xml_writer.writeEndElement();
    }
    xml_writer.writeEndElement();
    xml_writer.writeEmptyElement("port");
    xml_writer.writeAttribute("port", port);
    xml_writer.writeAttribute("baud_rate", QString::number(baud_rate));
    xml_writer.writeEndElement();
    xml_writer.writeEndDocument();
    open_file.close();
}

void Config::xml_read(){
    int baud_rate = 9600;
    QString port = "COM4";
    std::map<int,QString> buttons;
    if(QFile(file).exists()){
        QFile open_file = QFile(file);
        open_file.open(QFile::ReadWrite);
        QXmlStreamReader xml_reader(&open_file);
        while(!xml_reader.atEnd()){
            QXmlStreamReader::TokenType type = xml_reader.readNext();
            if(type == QXmlStreamReader::StartElement){
                if(xml_reader.name().toString() == "buttons"){
                    while(xml_reader.readNextStartElement()){
                        QString tkn = xml_reader.name().toString();
                        buttons[button_indexer(tkn)] = xml_reader.readElementText();
                    }
                }
                if(xml_reader.name().toString() == "port"){
                    QXmlStreamAttributes attr = xml_reader.attributes();
                    port = attr.value("port").toString();
                    baud_rate = attr.value("baud_rate").toInt();
                }
            }
        }
        open_file.close();
    }
    emit Config::content_ready(baud_rate,port,buttons);
}

int Config::button_indexer(QString btn){
    static QRegularExpression btn_pattern("button_([0-9]+)");
    QRegularExpressionMatch match = btn_pattern.match(btn);
    return match.captured(1).toInt();
}
