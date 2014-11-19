import re
import sys

class ProgramParse:
	def __init__(self, programText):
		self.text = programText
		self.variableTypes = { "int", "double", "float", "string", "uint8_t", "uint16_t", "uint32_t", "uint64_t", "int8_t", "int16_t", "int32_t", "int64_t", "char", "char16_t", "char32_t", "bool", "short", "wchar_t", "size_t", "void"}

		# keeps track of user defined variables and types and 
		# defines
		self.definedSymbols = set()

		self.tokens = []
		
		self.macros = []
		
		self.defines = []

		self.tokenPos = 0

	# will parse the program file to remove comments, save macros, get variable names and tokenize it
	def parse(self):
		self.__removeComments()
		self.__findAndRemoveMacros()
		self.__preprocess()
		self.__getVariableNames()
		self.__getTokens()

	# gets the total number of tokens in file
	def numWords(self):
		return len(self.tokens)

	# get the number of tokens left
	def numWordsRemaining(self):
		return len(self.tokens) - self.tokenPos

	# gets the next n tokens from the program
	def getWords(self, n):
		if (self.tokenPos + n > len(self.tokens)):
			raise Exception("Not Enough Words")

		phrase = ""
		for x in range(n):
			phrase += self.tokens[self.tokenPos + x] + " "

		# advances token position
		self.tokenPos += n
		return phrase

	# separates the processed files (stripped of comments and macros)
	# into tokens
	def __getTokens(self):
		# we can't split up strings across multiple defines, so each string however big must be one token
		lastPos = 0
		pos = self.text.find("\"")
		posEnd = -1
		while (pos != -1):
			tempText = self.text[lastPos:pos]
			words = tempText.split()
			for word in words:
				self.tokens.append(word)
			
			#find ending quote
			posEnd = self.text.find("\"", pos + 1)
			self.tokens.append(self.text[pos:posEnd + 1])
			lastPos = posEnd + 1
			pos = self.text.find("\"", posEnd + 1)

		if (posEnd != -1):
			tempText = self.text[posEnd + 1:]
			words = tempText.split()
			for word in words:
				self.tokens.append(word)
		else:
			words = self.text.split()
			for word in words:
				self.tokens.append(word)

	# gets the names of variables and types defined in the program
	def __getVariableNames(self):
		# finds defined classes and structs
		definedTypes = re.findall(ProgramParse.classStructRegex, self.text)
		for type_t in definedTypes:
			self.variableTypes.add(type_t)
			self.definedSymbols.add(type_t)

		# finds defined variables
		variableRegex = "(";
		for variable in self.variableTypes ^ {"int"}:
			variableRegex += variable + "|"
		variableRegex += "int)"
		variableRegex += " {0,}\*{0,1}&{0,2} +\*{0,1}&{0,2}(.+)"

		variables = re.findall(variableRegex, self.text)
		for variable in variables:
			self.__parseVariables(variable)

	# processes a variable string given by the variable Regex in __getVariableNames
	def __parseVariables(self, variable):
		name = variable[1]

		for char in "=;({:":
			pos = name.find(char)
			if (pos >= 0):
				name = name[:pos]
		
		# looking for multiple definitions
		names = name.split(",");
		for var in names:
			var = var.strip()
			if (var == ""):
				continue # if there's nothing left, go on
			self.definedSymbols.add(var)

	# removes all macros and saves them
	def __findAndRemoveMacros(self):
		self.__findAndRemovePattern("#include", "\n", self.macros)
		self.__findAndRemovePattern("using namespace", ";", self.macros)
		self.__findAndRemovePattern("#define", "\n", self.defines)

	# removes block and line comments
	def __removeComments(self):
		self.__findAndRemovePattern("/*", "*/")
		self.__findAndRemovePattern("//", "\n")

	# pre processes text so that regex can work properly
	def __preprocess(self):
		# making sure there is a new line after every semicolon
		self.text = self.text.replace(";", ";\n")

	# regex to find classes and structs
	classStructRegex = "(?:class|struct) {0,}([a-zA-Z0-9_-]+)"

	# finds and removes all instances of a pattern 
	# that begins with startText and ends with endText in text
	# and removes them from it
	def __findAndRemovePattern(self, startText, endText, setToAdd = None):
		start = self.text.find(startText)
		while (start != -1):
			end = self.text.find(endText, start)
			if (end == -1):
				break
			if (setToAdd != None):
				setToAdd.append(self.text[start:end + 1])
			self.text = self.text[:start] + self.text[end + len(endText):]
			start = self.text.find(startText)



