from os import system, name
import math

# define our clear function
def clear():
    # for windows
    if name == 'nt':
        _ = system('cls')
    # for mac and linux(here, os.name is 'posix')
    else:
        _ = system('clear')

def printastline(n):
	for x in range(n + 4):
		print("*",end='', flush=True)
	print()

def printstringast(string , n , index, prntIndex = True):
	print("*",end='', flush=True)
	l2 = int((n - len(string))/2)
	if (index-2) > 0:
		l1 = l2 + ((n - len(string))%2) - int(math.log10(index - 2))
	else:
		l1 = l2 + ((n - len(string))%2)
	for x in range(l1):
		print(" ",end='', flush=True)
	if index > 2 and prntIndex:
		print(index-2,end='', flush=True)
		print("-" + string,end='', flush=True)
	else:
		print("  " + string,end='', flush=True)
	for x in range(l2):
		print(" ",end='', flush=True)
	print("*")
	
class MyGUIPage:
	def __init__(self , title, spacing = 6):
		self.spacing = spacing
		#self.color = "color " + color
		self.barlen = len(title) + self.spacing
		self.num = 3
		self.stringarray = [title , ""]
	
	def addOptions(self,string):
		self.opt = string
		if self.barlen <= len(string):
			self.barlen = len(string) + self.spacing
 
	def addstrings(self,strings):
		for x in strings:
			self.num = self.num + 1
			if self.barlen <= len(x):
				self.barlen = len(x) + self.spacing
			self.stringarray.append(x)
	
	def addstring(self,string):
		self.num = self.num + 1
		if self.barlen <= len(string):
			self.barlen = len(string) + self.spacing
		self.stringarray.append(string)

	def printpage(self, prntIndex = True, opt = False):
		clear()
		#system(self.color)
		printastline(self.barlen)
		for x in range(1,self.num):
			printstringast(self.stringarray[x-1],self.barlen,x,prntIndex)
		printastline(self.barlen)
		if(opt):
			printstringast(self.opt,self.barlen,0)
			printastline(self.barlen)
	
	def getstring(self, index):
		return self.stringarray[index]
	
	def modstring(self,string,index):
		self.stringarray[index] = string
		if self.barlen <= len(string):
			self.barlen = len(string) + self.spacing
	
	def clearstring(self):
		title = self.stringarray[0]
		self.barlen = len(title) + self.spacing
		self.num = 3
		self.stringarray = [title , ""]
	

class MyGUIMenu:
	def __init__(self):
		self.pagesdict = dict()
		
	def addpage(self , page, namepage):
		self.pagesdict[namepage] = page

	
	def printmenupage(self, name, prntIndex = True, opt = False):
		self.pagesdict[name].printpage(prntIndex,opt)