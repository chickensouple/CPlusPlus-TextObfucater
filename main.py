import re
import sys
from programParse import *
from textParse import *

if (len(sys.argv) < 4):
	print("Please give a file")
	exit()

# parsing program file
programFile = open(sys.argv[1], 'r')
programParser = ProgramParse(programFile.read())
programParser.parse()
programFile.close()

# parsing text file
textFile = open(sys.argv[2], 'r')
textParser = TextParse(textFile.read())
textParser.parse()
textFile.close()

# gets number of words from each file
programNumWords = programParser.numWords()
textNumWords = textParser.numWords()

# if there are more program words than text words, we will
# assign pNum(number of program words per define) to be as close as possible such that textNumWords * pNum = programNumWords
# assign tNum (number of text words per define)
# assign numDefines to be the number of textwords
# if more text words than program words, we will do the opposite for pNum, tNum and numDefines
if (programNumWords > textNumWords):
	pNum = int(programNumWords / textNumWords)
	tNum = 1
	numDefines = textNumWords
else:
	pNum = 1
	tNum = int(textNumWords / programNumWords)
	numDefines = programNumWords

# opens up the output file
outFile = open(sys.argv[3], 'w')

# print macros
for macro in programParser.macros:
	outFile.write(str(macro) + "\n")

# print defines
for define in programParser.defines:
	outFile.write(str(define) + "\n")

newProgram = [] # list to hold all the new defines
for x in range(numDefines - 1):
	# gets the program words
	programWords = programParser.getWords(pNum)
	# gets the text words
	textWords = textParser.getWords(tNum, programParser.variableTypes, programParser.definedSymbols)
	# add define to newProgram and write it to file
	newProgram.append(textWords)
	outFile.write("#define " + textWords + " " + programWords + "\n")

# getting the remaining words for each for the last define
programWords = programParser.getWords(programParser.numWordsRemaining())
textWords = textParser.getWords(textParser.numWordsRemaining(), programParser.variableTypes, programParser.definedSymbols)
outFile.write("#define " + textWords + " " + programWords + "\n\n")
newProgram.append(textWords)

# writes only 5 textWords per line
count = 0
for word in newProgram:
	outFile.write(word + " ")
	count += 1
	if (count == 5):
		count = 0
		outFile.write("\n")

outFile.close()


