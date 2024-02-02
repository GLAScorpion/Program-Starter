import board 
import usb_cdc
from adafruit_debouncer import Debouncer
import asyncio
import async_keypad
row_pins = (board.GP2,board.GP3,board.GP4,board.GP5)
col_pins = (board.GP6,board.GP7,board.GP8,board.GP9)

async def ser_conn(keypad:async_keypad.AsyncKeypad,ready_event,wait_event):
    mex = bytearray(1)
    while True:
            await ready_event.wait()
            ready_event.clear()
            print("Key Detected: " + str(keypad.key))
            mex[0] = keypad.key
            usb_cdc.data.write(mex)
            wait_event.set()
            await asyncio.sleep(0)

async def main():
    ready_event = asyncio.Event()
    wait_event = asyncio.Event()
    keypad = async_keypad.AsyncKeypad(row_pins,col_pins,ready_event,wait_event)
    button_task = asyncio.create_task(keypad.button_mon())
    ser_task = asyncio.create_task(ser_conn(keypad,ready_event,wait_event))
    await asyncio.gather(button_task,ser_task)
    
    
asyncio.run(main())
