#include "config.h"
Config::Config(char* filename)
    :file{filename}
{
    bool exist = file.exists();
    file.open(QIODevice::ReadWrite);
    xml_writer = new QXmlStreamWriter(&file);
    xml_reader = new QXmlStreamReader(&file);
    xml_writer->setAutoFormatting(true);
    if (!exist){
        xml_write();
        /*
        xml_writer->writeStartDocument();
        xml_writer->writeStartElement("config");
        xml_writer->writeStartElement("buttons");
        xml_writer->writeEndElement();
        xml_writer->writeEmptyElement("port");
        xml_writer->writeAttribute("port","COM4");
        xml_writer->writeAttribute("baud_rate","9600");
        xml_writer->writeEndElement();
        xml_writer->writeEndDocument();
        */
    }else{
        while(!xml_reader->atEnd()){
            QXmlStreamReader::TokenType type = xml_reader->readNext();
            if(type == QXmlStreamReader::StartElement){
                if(xml_reader->tokenString() == "buttons"){
                    while(xml_reader->readNextStartElement()){
                        std::string tkn = xml_reader->tokenString().toStdString();
                        buttons[button_indexer(tkn)] = xml_reader->readElementText().toStdString();
                    }
                }
                if(xml_reader->tokenString() == "port"){
                    QXmlStreamAttributes attr = xml_reader->attributes();
                    port = attr.value("port").toString().toStdString();
                    baud_rate = attr.value("baud_rate").toInt();

                }
            }
        }
    }
}

void Config::SetButton(int index, std::string cmd){
    buttons[index] = cmd;
    xml_write();
}

void Config::SetPort(std::string port){
    this->port = port;
    xml_write();
}
void Config::SetBaudRate(int rate){
    this->baud_rate = rate;
    xml_write();
}

void Config::xml_write(){
    xml_writer->writeStartDocument();
    xml_writer->writeStartElement("config");
    for(auto i = buttons.begin();i != buttons.end();i++){
        xml_writer->writeStartElement("buttons");
        xml_writer->writeStartElement("buttons_" + std::to_string(i->first));
        xml_writer->writeCharacters(i->second);
        xml_writer->writeEndElement();
    }
    xml_writer->writeEndElement();
    xml_writer->writeEmptyElement("port");
    xml_writer->writeAttribute("port", port);
    xml_writer->writeAttribute("baud_rate", std::to_string(baud_rate));
    xml_writer->writeEndElement();
    xml_writer->writeEndDocument();
}

int Config::button_indexer(std::string btn){
    int res = 0;
    for(int index = btn.length() - 1; btn[index] != '_' && std::isdigit(btn[index]); index--){
        res += btn[index] - '0';
    }
    return res;
}
