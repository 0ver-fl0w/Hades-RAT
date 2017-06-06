# -*- coding: utf-8 -*-
import sys, time
from termcolor import colored

class Colours:
   RED = "\x1B[31m"
   GRN = "\x1B[32m"
   YEL = "\x1B[33m"
   BLU = "\x1B[34m"
   MAG = "\x1B[35m"
   CYN = "\x1B[36m"
   WHT = "\x1B[37m"
   RESET = "\x1B[0m"

   BOLDRED = "\x1B[1m\033[31m"
   BOLDGRN = "\x1B[1m\033[32m"
   BOLDYEL = "\x1B[1m\033[33m"
   BOLDBLU = "\x1B[1m\033[34m"
   BOLDMAG = "\x1B[1m\033[35m"
   BOLDCYN = "\x1B[1m\033[36m"
   BOLDWHT = "\x1B[1m\033[37m"


def main():
        print Colours.BOLDBLU + "              ______ _ _        _____"                                 
	print "             |  ____(_) |      |  __ \ "                                
	print "             | |__   _| | ___  | |__) |   _ _ __ ___  _ __   ___ _ __ "
	print "             |  __| | | |/ _ \ |  ___/ | | | '_ ` _ \| '_ \ / _ \ '__|"
	print "             | |    | | |  __/ | |   | |_| | | | | | | |_) |  __/ |"   
	print "             |_|    |_|_|\___| |_|    \__,_|_| |_| |_| .__/ \___|_|"   
	print "                           ______                    | |"              
	print "                          |______|                   |_|\n"              


	print Colours.BOLDGRN + "			[" + Colours.BOLDWHT + "*" + Colours.BOLDGRN + "]" + Colours.BOLDWHT + " File Pumper Initiating..."
	filename = raw_input(Colours.BOLDGRN + "			[" + Colours.BOLDWHT + "*" + Colours.BOLDGRN + "]" + Colours.BOLDWHT + " Please Input The File Name: ")
	size = input(Colours.BOLDGRN + "			[" + Colours.BOLDWHT + "*" + Colours.BOLDGRN + "]" + Colours.BOLDWHT + " Please Input The Increase Size: ")
	mbkb = raw_input(Colours.BOLDGRN + "			[" + Colours.BOLDWHT + "*" + Colours.BOLDGRN + "]" + Colours.BOLDWHT + " Please Input The Unit (KB/MB): ")
	
	f = open(filename, "ab")
	if mbkb == "KB":
	    b_size = size * 1024
	elif mbkb == "MB":
	    b_size = size * 1048576
	else:
	    print Colours.BOLDRED + "				[!] Please Use KB Or MB [!]\n"
	    sys.exit(0)
	
	BufSize = 256
	for i in range(b_size/BufSize):
	    f.write(str('0' * BufSize))
	f.close()
	print Colours.BOLDGRN + "			[" + Colours.BOLDWHT + "*" + Colours.BOLDGRN + "]" + Colours.BOLDWHT + " Finished Pumping", filename, "with", size, mbkb, "!"
	time.sleep(1)
	sys.exit(0)

if __name__ == "__main__":
	main()
