import conflib
import argparse
import cli
import gui
parser = argparse.ArgumentParser(prog="Program Starter Manager")
parser.add_argument("-f","--filename",action='store_const',default="Config.xml")
parser.add_argument("-c","--cli",action='store_true',dest='cli_opt',default=False)
args = parser.parse_args()
config = conflib.Config(args.filename)

if __name__ == "__main__":
    if(args.cli_opt):
        cli.CLI(config)
    else:
        print("starting gui")
        gui.GUI()
