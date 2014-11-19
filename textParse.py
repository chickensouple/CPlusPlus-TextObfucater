import re
import sys

class TextParse:
	def __init__(self, text):
		self.text = text

		# list of text not yet used
		self.wordsList = []

		# set of used words or phrases
		self.usedSet = set()

		self.wordsListPos = 0

	# parses the text file (prepares it for reading from and cleans it up)
	def parse(self):
		words = self.text.split()
		# replacing all illegal characters with underscores
		for word in words:
			word = list(word)
			for i in range(len(word)):
				if (not word[i].isalnum()):
					word[i] = "_"
			self.wordsList.append("".join(word))

	# n is the number of words to get
	def getWords(self, n, typeNames, variableNames):
		if (self.wordsListPos + n > len(self.wordsList)):
			raise Exception("Not Enough Words")

		phrase = ""
		for word in self.wordsList[self.wordsListPos:self.wordsListPos + n - 1]:
			phrase += word + "_"
		phrase += self.wordsList[self.wordsListPos + n - 1]
		
		# if we have already used the phrase, keep adding underscores
		while (phrase in self.usedSet):
			phrase += "_"

		# if it is the name of a type, add underscores
		while (phrase in typeNames):
			phrase += "_"

		# if it is the name of a variable, add underscores
		while (phrase in variableNames):
			phrase += "_"

		# add phrase to our used set
		self.usedSet.add(phrase)

		#advance word list position
		self.wordsListPos += n
		return phrase

	# gets number of words remaining in text file
	def numWordsRemaining(self):
		return len(self.wordsList) - self.wordsListPos

	# gets total number of words in file
	def numWords(self):
		return len(self.wordsList)
