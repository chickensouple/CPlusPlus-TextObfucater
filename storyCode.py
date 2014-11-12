import re
import sys
from programParse import *

if (len(sys.argv) != 2):
	print("Please give a file")
	exit()

programFile = open(sys.argv[1], 'r')

programString = programFile.read()

programParser = ProgramParse(programString)
programParser.parse()



