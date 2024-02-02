import digitalio
from adafruit_debouncer import Debouncer
import asyncio

class AsyncKeypad:
    key = -1
    __rows = list()
    __cols = list()
    __buttons = list()
    __down_btn = list()

    def __init__(self,row_pins:tuple, col_pins:tuple,ready_event, wait_event):
        self.__ready_event = ready_event
        self.__wait_event = wait_event
        for i in range(len(row_pins)):
            self.__rows.append(digitalio.DigitalInOut(row_pins[i]))
            self.__rows[i].switch_to_output(drive_mode=digitalio.DriveMode.PUSH_PULL)

        for i in range(len(col_pins)):
            self.__cols.append(digitalio.DigitalInOut(col_pins[i]))
            self.__cols[i].switch_to_input(pull=digitalio.Pull.DOWN)
            
        for y in range(len(row_pins)):
            for x in range(len(col_pins)):
                self.__down_btn.append(False)
                self.__buttons.append(Debouncer(self.__cols[x]))
        
    async def button_mon(self):
        while(True):
            for y in range(len(self.__rows)):
                self.__rows[y].value = True
                for x in range(len(self.__cols)):
                    self.__buttons[x + 4*y].update()
                    if(self.__buttons[x + 4*y].fell):
                        self.__down_btn[x + 4*y] = True
                    if(self.__buttons[x + 4*y].rose):
                        if(self.__down_btn[x + 4*y]):
                            self.key = x + 4*y
                            self.__ready_event.set()
                            await self.__wait_event.wait()
                            self.__wait_event.clear()
                            self.__down_btn[x + 4*y] = False 
                self.__rows[y].value = False
            await asyncio.sleep(0)