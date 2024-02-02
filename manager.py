import conflib
import argparse
import mygui

parser = argparse.ArgumentParser(prog="Program Starter Manager")
parser.add_argument("-f","--filename",action='store_const',default="Config.xml")
args = parser.parse_args()
config = conflib.Config(args.filename)

class Cursor:
    def __init__(self):
        self.cursor = 0
    def setter(self, n:int):
        self.cursor = n

def main():
    global main_page
    global button_page
    global device_page
    global menu
    cursor = Cursor()
    menu = mygui.MyGUIMenu()
    main_page = mygui.MyGUIPage("Main Menu")
    menu.addpage(main_page,"main_page")
    button_page = mygui.MyGUIPage("Button Associations")
    menu.addpage(button_page,"button_page")
    main_page.addstrings(("[B] Buttons","[D] Device Setup","[Q] Quit"))
    device_page = mygui.MyGUIPage("Device Configuration")
    menu.addpage(device_page,"device_page")
    config.bindGUIPage(menu)
    while True:
        match cursor.cursor:
            case 0:
                main_options(cursor)
            case 1:
                button_options(cursor)
            case 2:
                device_options(cursor)
            case -1:
                break
def device_options(cursor:Cursor):
    page = "device_page"
    device_page.addOptions("[E] Edit [B] Back")
    while True:
        menu.printmenupage(page,False,True)
        choice = input(">> ")
        match choice:
            case "B":
                cursor.setter(0)
                break
            case "E":
                mex = "Insert the port. Type \"[ABORT]\" to abort"
                while True:
                    menu.printmenupage(page,False)
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
                        config.editDevice(choice,rate)
                        break
                    else:
                        mex = "Not an integer baud rate, retry\nInsert the port. Type \"[ABORT]\" to abort"
                    
        
def main_options(cursor:Cursor):
    page = "main_page"
    while True:
        menu.printmenupage(page,False)
        choice = input(">> ")
        match choice:
            case "B":
                cursor.setter(1)
                break
            case "Q":
                cursor.setter(-1)
                break
            case "D":
                cursor.setter(2)
                break
            case _:
                pass
        _ = input()
    
def button_options(cursor:Cursor):
    page = "button_page"
    button_page.addOptions("[B] Back [N] New [E] Edit [R] Remove")
    while True:
        menu.printmenupage(page,False,True)
        choice = input(">> ")
        match choice:
            case "B":
                cursor.setter(0)
                break
            case "N":
                mex = "Type the new button number. Type \"[ABORT]\" to abort"
                while True:
                    menu.printmenupage(page,False)
                    print(mex)
                    choice = input("[NEW]>> ")
                    if (choice == "[ABORT]"):
                        break
                    if (choice.isnumeric()):
                        print("Type the command to execute")
                        cmd_choice = input("[NEW:" + str(choice) + "]>> ")
                        if(config.addButtonMapping(int(choice),cmd_choice)):
                            break
                        else:
                            mex = "Button already registered"
                    else:
                        mex = "Not an integer, retry"
                        
            case "E":
                mex = "Type the button number. Type \"[ABORT]\" to abort"
                while True:
                    menu.printmenupage(page, False)
                    print(mex)
                    choice = input("[EDIT]>> ")
                    if (choice == "[ABORT]"):
                        break
                    if (choice.isnumeric()):
                        print("Type the new command to execute")
                        cmd_choice = input("[EDIT:" + str(choice) + "]>> ")
                        if(config.editButton(int(choice),cmd_choice)):
                            break
                        else:
                            mex = "Button not registered"
                    else:
                        mex = "Not an integer, retry"
            case "R":
                mex = "Type the button number. Type \"[ABORT]\" to abort"
                while True:
                    menu.printmenupage(page, False)
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
                        if(config.removeButton(int(choice))):
                            break
                        else:
                            mex = "Button not registered"
                    else:
                        mex = "Not an integer, retry"
                    

if __name__ == "__main__":
    main()
'''

print(config.getButtons())

print(config.getCmd(0))

'''