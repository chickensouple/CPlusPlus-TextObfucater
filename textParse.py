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

	def parse(self):
		words = self.text.split()
		for word in words:
			word = list(word)
			for i in range(len(word)):
				if (not word[i].isalnum()):
					word[i] = "_"
			self.wordsList.append("".join(word))

	# n is the number of words to get
	def getWords(self, n = 1):
		if (self.wordsListPos + n > len(self.wordsList)):
			raise Exception("Not Enough Words")

		phrase = ""
		for word in self.wordsList[self.wordsListPos:self.wordsListPos + n - 1]:
			phrase += word + "_"
		phrase += self.wordsList[self.wordsListPos + n - 1]
		
		while (phrase in self.usedSet):
			phrase += "_"

		self.usedSet.add(phrase)
		self.wordsListPos += n
		return phrase

	def numWordsRemaining(self):
		return len(self.wordsList) - self.wordsListPos

	def numWords(self):
		return len(self.wordsList)
