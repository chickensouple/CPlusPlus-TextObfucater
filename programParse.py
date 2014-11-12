import re
import sys

class ProgramParse:
	def __init__(self, programText):
		self.text = programText
		self.variableTypes = { "int", "double", "float", "string", "uint8_t", "uint16_t", "uint32_t", "uint64_t", "int8_t", "int16_t", "int32_t", "int64_t", "char", "char16_t", "char32_t", "bool", "short", "wchar_t", "size_t", "void"}

		# keeps track of user defined variables and types and #defines
		self.definedSymbols = set()

		self.macros = set()
		self.defines = set()

	# the only external function you need to call
	# will parse the program file
	def parse(self):
		self.__removeComments()
		self.__findAndRemoveMacros()
		self.__preprocess()
		self.__getVariableNames()

	def __getVariableNames(self):
		# classes and structs
		definedTypes = re.findall(ProgramParse.classStructRegex, self.text)
		for type_t in definedTypes:
			self.variableTypes.add(type_t)
			self.definedSymbols.add(type_t)

		variableRegex = "(";
		for variable in self.variableTypes ^ {"int"}:
			variableRegex += variable + "|"
		variableRegex += "int)"
		variableRegex += " {0,}\*{0,1}&{0,2} {0,}(.+) {0,}"
		# print(variableRegex)

		variables = re.findall(variableRegex, self.text)
		for variable in variables:
			print(variable)

	def __findAndRemoveMacros(self):
		self.__findAndRemovePattern("#include", "\n", self.macros)
		self.__findAndRemovePattern("using namespace", ";", self.macros)
		self.__findAndRemovePattern("#define", "\n", self.defines)

	def __removeComments(self):
		self.__findAndRemovePattern("/*", "*/")
		self.__findAndRemovePattern("//", "\n")

	# pre processes text so that regex can work properly
	def __preprocess(self):
		# making sure there is a new line after every semicolon
		self.text = self.text.replace(";", ";\n")

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
				setToAdd.add(self.text[start:end])
			self.text = self.text[:start] + self.text[end + len(endText):]
			start = self.text.find(startText)



