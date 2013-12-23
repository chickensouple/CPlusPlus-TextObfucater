#ifndef _file_classes
#define _file_classes

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// declaring classes
class GeneralFile;
class ProgramFile;
class TextFile;

// exception classes
class NotParsed {};
class InvalidArguments {};
class FileNotOpen {};


// base class for files
class GeneralFile {
protected:
	// input filestream containing file
	std::ifstream fileStream;

	// vector of strings holding each parsed file word
	std::vector<std::string> parsedFile;

	// boolean value representing whether parsedFile holds the parsed text yet
	bool isParsed;

	// EFFECTS: cleans sentence of extraneous underscores (max one underscore between words)
	// adds extra underscores to the end if sentence already exists
	static std::string cleanSentence(const std::string & sentence, const std::vector<std::string> & currSentences);

	// EFFECTS: checks if word has a duplicate in currWords
	static bool duplicateWord(const std::string & word, const std::vector<std::string> & currWords);
public:
	GeneralFile(const char* fileName);

	// EFFECTS: closes filestream
	void closeFile();

	// EFFECTS: returns if filestream is open
	bool isOpen() const;

	// REQUIRES: text has to be parsed
	// EFFECTS: gets number of words
	int numWords() const;

	// REQUIRES: ProgramFile and TextFile have been parsed
	// EFFECTS: writes story file into a new file
	// MODIFIES: new file
	static void createStoryFile(const ProgramFile & program, const TextFile & text, const char* newFileName, int wordsPerLine);

	virtual void parse() = 0;
};

// class for text file
class TextFile : public GeneralFile {
friend class GeneralFile;
private:
	// string of punctuation to be deleted
	const std::string delPunctList;

	// string of punctuation to be replaced by underscores
	const std::string replacePunctList;

	// vector of strings for c++ keywords
	std::vector<std::string> keyWords;

	// EFFECTS: cleans word of punctuation and makes sure its unique
	std::string cleanWord(std::string & word, std::vector<std::string> & currWords) const;
	
	// checks if word is not just a string of underscores
	bool isWord(std::string & word) const;
public: 
	TextFile(const char * fileName);

	// REQUIRES: filestream has to be open
	// EFFECTS: takes a file and parses it into a vector of strings as well as cleaning each word of punctuation and getting rid of repetitions and keywords
	// also closes the file
	// MODIFIES: internal structure of class
	virtual void parse();
};

// class for c++ file
class ProgramFile : public GeneralFile {
friend class GeneralFile;
private:
	// file name for temp file
	const char* tempFileName;

	// vector of strings to store includes
	std::vector<std::string> includes;

	// vector of strings to store function names, class names, struct names, enum names, variable names
	std::vector<std::string> programWords;

	// EFFECTS: checks if word contains an even number of quotes
	static bool quotesPaired(const std::string & word);

	// REQUIRES: fileStream must be open
	// EFFECTS: creates a temporary file that cleans the original program file. i.e. erases comments gets rid of #include's
	// returns a list of #include's
	// MODIFIES: internal structure of class
	// note: is called by parse()
	void preprocess();
public:
	ProgramFile(const char* fileName);


	// REQUIRES: fileStream is open
	// EFFECTS: takes a file and parses it into a vector of strings as well as making sure quotes are closed in each "word"
	// MODIFIES: internal structure of class
	virtual void parse();
};

#endif