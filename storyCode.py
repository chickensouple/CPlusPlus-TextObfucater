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

programNumWords = programParser.numWords()
textNumWords = textParser.numWords()

if (programNumWords > textNumWords):
	pNum = int(programNumWords / textNumWords)
	tNum = 1
	numWords = textNumWords
else:
	pNum = 1
	tNum = int(textNumWords / programNumWords)
	numWords = programNumWords

outFile = open(sys.argv[3], 'w')


# print macros
for macro in programParser.macros:
	outFile.write(str(macro) + "\n")

for define in programParser.defines:
	outFile.write(str(define) + "\n")

newProgram = [] # list to hold all the new defines
for x in range(numWords - 1):
	programWords = programParser.getWords(pNum)
	textWords = textParser.getWords(tNum)
	while (textWords in programParser.variableTypes):
		textWords += "_"

	textParser.usedSet.add(textWords)
	newProgram.append(textWords)
	outFile.write("#define " + textWords + " " + programWords + "\n")

programWords = programParser.getWords(programParser.numWordsRemaining())
textWords = textParser.getWords(textParser.numWordsRemaining())
while (textWords in programParser.variableTypes):
		textWords += "_"
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


