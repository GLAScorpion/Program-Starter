import mygui
import conflib

class CLI:
    
    def __init__(self,config:conflib.Config):
        self.config = config
        self.cursor = 0
        self.menu = mygui.MyGUIMenu()
        self.main_page = mygui.MyGUIPage("Main Menu")
        self.menu.addpage(self.main_page,"main_page")
        self.button_page = mygui.MyGUIPage("Button Associations")
        self.menu.addpage(self.button_page,"button_page")
        self.main_page.addstrings(("[B] Buttons","[D] Device Setup","[Q] Quit"))
        self.device_page = mygui.MyGUIPage("Device Configuration")
        self.menu.addpage(self.device_page,"device_page")
        self.config.bindGUIPage(self.menu)
        while True:
            match self.cursor:
                case 0:
                    self.main_options()
                case 1:
                    self.button_options()
                case 2:
                    self.device_options()
                case -1:
                    break
                
    def device_options(self):
        page = "device_page"
        self.device_page.addOptions("[E] Edit [B] Back")
        while True:
            self.menu.printmenupage(page,False,True)
            choice = input(">> ")
            match choice:
                case "B":
                    self.cursor = 0
                    break
                case "E":
                    mex = "Insert the port. Type \"[ABORT]\" to abort"
                    while True:
                        self.menu.printmenupage(page,False)
                        print(mex)
                        choice = input("[EDIT]>> ")
                        if (choice == "[ABORT]"):
                                break
                        mex = "Insert the baud rate. Type \"[ABORT]\" to abort"
                        print(mex)
                        rate = input("[EDIT]>> ")
                        if (rate == "[ABORT]"):
                            break
                        if (rate.isnumeric()):
                            self.config.editDevice(choice,rate)
                            break
                        else:
                            mex = "Not an integer baud rate, retry\nInsert the port. Type \"[ABORT]\" to abort"
                        
            
    def main_options(self):
        page = "main_page"
        while True:
            self.menu.printmenupage(page,False)
            choice = input(">> ")
            match choice:
                case "B":
                    self.cursor = 1
                    break
                case "Q":
                    self.cursor = -1
                    break
                case "D":
                    self.cursor = 2
                    break
                case _:
                    pass
            _ = input()
        
    def button_options(self):
        page = "button_page"
        self.button_page.addOptions("[B] Back [N] New [E] Edit [R] Remove")
        while True:
            self.menu.printmenupage(page,False,True)
            choice = input(">> ")
            match choice:
                case "B":
                    self.cursor = 0
                    break
                case "N":
                    mex = "Type the new button number. Type \"[ABORT]\" to abort"
                    while True:
                        self.menu.printmenupage(page,False)
                        print(mex)
                        choice = input("[NEW]>> ")
                        if (choice == "[ABORT]"):
                            break
                        if (choice.isnumeric()):
                            print("Type the command to execute")
                            cmd_choice = input("[NEW:" + str(choice) + "]>> ")
                            if(self.config.addButtonMapping(int(choice),cmd_choice)):
                                break
                            else:
                                mex = "Button already registered"
                        else:
                            mex = "Not an integer, retry"
                            
                case "E":
                    mex = "Type the button number. Type \"[ABORT]\" to abort"
                    while True:
                        self.menu.printmenupage(page, False)
                        print(mex)
                        choice = input("[EDIT]>> ")
                        if (choice == "[ABORT]"):
                            break
                        if (choice.isnumeric()):
                            print("Type the new command to execute")
                            cmd_choice = input("[EDIT:" + str(choice) + "]>> ")
                            if(self.config.editButton(int(choice),cmd_choice)):
                                break
                            else:
                                mex = "Button not registered"
                        else:
                            mex = "Not an integer, retry"
                case "R":
                    mex = "Type the button number. Type \"[ABORT]\" to abort"
                    while True:
                        self.menu.printmenupage(page, False)
                        print(mex)
                        choice = input("[REMOVAL]>> ")
                        if (choice == "[ABORT]"):
                            break
                        if (choice.isnumeric()):
                            mex = "Please confirm removal. Y or N\n>> "
                            confirm = ""
                            while confirm != "N" or confirm != "Y":
                                confirm = input(mex)
                                if(confirm == "Y"):
                                    break
                                elif(confirm == "N"):
                                    break
                            if(confirm == "N"):
                                break
                            if(self.config.removeButton(int(choice))):
                                break
                            else:
                                mex = "Button not registered"
                        else:
                            mex = "Not an integer, retry"