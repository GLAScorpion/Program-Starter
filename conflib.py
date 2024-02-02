import mygui
from types import NoneType
from lxml import etree
import os
import re
class Config:
    buttons_dict = dict()
    config = etree.Element("config") 
    buttons = etree.SubElement(config,"buttons") 
    port = etree.SubElement(config,"port",port="COM4",baud_rate = "9600")
    menu = NoneType
    def __init__(self,file):
        self.file = file
        if(not os.path.isfile(file)):
            self.__write_conf()
        else:
            tree = etree.parse(file) 
            self.config = tree.getroot()
            for conf in self.config:
                if(conf.tag == "buttons"):
                    self.buttons = conf
                if(conf.tag == "port"):
                    self.port = conf
            for btn in self.buttons:
                self.buttons_dict[btn.tag] = btn.text
                
    def editDevice(self,port,baud_rate):
        self.port.attrib["port"] = port
        self.port.attrib["baud_rate"] = baud_rate
        self.__write_conf()
        
    def getDevice(self):
        return (self.port.attrib["port"],self.port.attrib["baud_rate"])
    
    def addButtonMapping(self,btn,cmd):
        if(self.config.xpath(".//buttons//button_"+str(btn))!=[]):
            return False
        tmp = etree.SubElement(self.buttons,"button_" + str(btn))
        tmp.text = cmd
        self.buttons_dict["button_" + str(btn)] = cmd
        self.__write_conf()
        return True
    
    def removeButton(self,btn):
        if "button_" + str(btn) in self.buttons_dict.keys():
            self.buttons.remove(self.buttons.find("button_" + str(btn)))
            self.buttons_dict.pop("button_" + str(btn))
            self.__write_conf()
            return True
        return False
    
    def editButton(self,btn,cmd):
        if "button_" + str(btn) in self.buttons_dict.keys():
            self.buttons.find("button_" + str(btn)).text = cmd
            self.buttons_dict["button_" + str(btn)] = cmd
            self.__write_conf()
            return True
        return False
    
    def getCmd(self,btn):
        return self.buttons_dict["button_" + str(btn)]
    
    def getButtons(self):
        res = list()
        for key in self.buttons_dict.keys():
            res.append(re.findall("button_([0-9])", key)[0])
        res.sort()
        return tuple(res)
    
    def __write_conf(self):
        if (self.menu != NoneType):
            button_page = self.menu.pagesdict["button_page"]
            port,rate = self.getDevice()
            self.menu.pagesdict["device_page"].clearstring()
            self.menu.pagesdict["device_page"].addstrings(("Port: " + port,"Baud Rate: " + rate))
            button_page.clearstring()
            for index in self.getButtons():
                button_page.addstring("Button " + str(index)+" >> " + self.getCmd(index))
        tree = etree.ElementTree(self.config)
        tree.write(self.file, pretty_print=True, xml_declaration=True, encoding='utf-8')
        
    def bindGUIPage(self, menu:mygui.MyGUIMenu):
        self.menu = menu
        port,rate = self.getDevice()
        self.menu.pagesdict["device_page"].addstrings(("Port: " + port,"Baud Rate: " + rate))
        for index in self.getButtons():
            self.menu.pagesdict["button_page"].addstring("Button " + str(index)+": " + self.getCmd(index))