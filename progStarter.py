import platform
import subprocess
import serial
import asyncio
import argparse
import conflib
import time

parser = argparse.ArgumentParser(prog="Program Starter Daemon")
parser.add_argument("-f","--filename",action='store_const',default="Config.xml")
args = parser.parse_args()
config = conflib.Config(args.filename)
port,rate = config.getDevice()

def wait_serial() -> serial.Serial:
    global ser
    while True:
        try:
            ser = serial.Serial(port,baudrate=int(rate))
            print("Connected on port " + port + " with rate "+ rate)
            return ser
        except:
            pass
        time.sleep(0)
    
    
async def serialmon(ser:serial.Serial):
    try:
        while True:
            val = ser.read(1)
            dec_val = int.from_bytes(val,"big")
            print("Button Pressed: " + str(dec_val))
            if str(dec_val) in config.getButtons():
                cmd = config.getCmd(dec_val)
                print("Starting " + cmd)
                subprocess.Popen(cmd)
            await asyncio.sleep(0)
    except:
        return

async def stop_mon():
    while True:
        user = input()
        if user == "Q":
            asyncio.get_running_loop().close()
            break
        await asyncio.sleep(0)

async def main():
    while True:
        ser = wait_serial()
        serial_task = asyncio.create_task(serialmon(ser))
        #stop_task = asyncio.create_task(stop_mon())
        await asyncio.gather(serial_task)
        await asyncio.sleep(0)

asyncio.run(main())