#include "fileClasses.h"

std::string GeneralFile::cleanSentence(const std::string & sentence, const std::vector<std::string> & currSentences) {

	std::string ret(sentence);
	std::vector<int> del;
	// looking for strings of underscores
	for (unsigned int i = 0; i < ret.size(); ++i) {
		if (ret[i] == '_') {
			// if i + 1 is out of bounds, short circuits the statement
			if (i + 1 != ret.size() && ret[i + 1] == '_') {
				del.push_back(i + 1);
			} else if (i == ret.size() - 1) {
				del.push_back(i);
			}
		}
	}

	// deleting underscores
	for (unsigned int i = 0; i < del.size(); ++i) {
		ret.erase(del[i] - i, 1);
	}

	// making sure sentence is unique
	while(duplicateWord(ret, currSentences)) {
		ret += "_";
	}
	return ret;
}

GeneralFile::GeneralFile(const char* fileName) : isParsed(false) {
	fileStream.open(fileName);
}

bool GeneralFile::duplicateWord(const std::string & word, const std::vector<std::string> & currWords) {
	for (unsigned int i = 0; i < currWords.size(); ++i) {
		if (word == currWords[i]) {
			return true;
		}
	}
	return false;
}

void GeneralFile::closeFile() {
	if (isOpen()) {
		fileStream.close();
	}
}

bool GeneralFile::isOpen() const{
	return fileStream.is_open();
}

int GeneralFile::numWords() const{
	if (isParsed) {
		return parsedFile.size();
	} else {
		throw NotParsed();
	}
}

void GeneralFile::createStoryFile(const ProgramFile & program, const TextFile & text, const char* newFileName, int wordsPerLine) {
	int ratio1 = program.numWords() / text.numWords();
	int ratio2 = text.numWords() / program.numWords();

	std::ofstream writeFile(newFileName);

	// writing includes
	for (unsigned int i = 0; i < program.includes.size(); ++i) {
		writeFile << program.includes[i] << std::endl;
	}
	writeFile << "\n";

	// if there are more words in program than in text
	if (ratio1 >= ratio2) {
		// writes the first textWords.size() - 1 #define's to file along (because the last one may have an irregular number of associated program words)
		for (int i = 0; i < text.numWords() - 1; ++i) {
			writeFile << "#define " << text.parsedFile[i] << " ";
			for (int j = 0; j < ratio1; ++j) {
				writeFile << program.parsedFile[ratio1 * i + j] << " ";
			}
			writeFile << std::endl;
		}

		// writing the last #define
		writeFile << "#define " << text.parsedFile[text.numWords() - 1] << " ";
		for (int i = (text.numWords() - 1) * ratio1; i < program.numWords(); ++i) {
			writeFile << program.parsedFile[i] << " ";
		}
		writeFile << "\n\n\n";

		// writing the textwords
		for (int i = 0; i < text.numWords(); ++i) {
			writeFile << text.parsedFile[i] << " ";
			if (i % wordsPerLine == 0 && i != 0) {
				writeFile << std::endl;
			}
		}
	} else {
	// if there are more words in text than in program

		//temp is for storing concatenated strings with the underscore
		std::vector<std::string> temp;

		//a string for building up a string concatenation
		std::string builder;

		// writing the first programWords.size() - 1 #define's
		for (int i = 0; i < program.numWords() - 1; ++i) {
			writeFile << "#define ";
			builder = "";
			for (int j = 0; j < ratio2; ++j) {
				if (j != ratio2 - 1) {
					builder += text.parsedFile[ratio2 * i + j] + "_";
				} else {
					builder += text.parsedFile[ratio2 * i + j];
				}
			}
			temp.push_back(GeneralFile::cleanSentence(builder, temp));
			writeFile << temp.back() << " " << program.parsedFile[i] << std::endl;
		}

		// writing the last #define
		writeFile << "#define ";
		builder = "";
		for (int i = (program.numWords() - 1) * ratio2; i < text.numWords(); ++i) {
			if (i != text.numWords() - 1) {
				builder += text.parsedFile[i] + "_";
			} else {
				builder += text.parsedFile[i];
			}
		}
		temp.push_back(cleanSentence(builder, temp));
		writeFile << temp.back() << " " << program.parsedFile[program.numWords() - 1] << "\n\n\n";

		// writing out whatever is in temp
		for (unsigned int i = 0; i < temp.size(); ++i) {
			writeFile << temp[i] << " ";
			if (i % (wordsPerLine / ratio2) == 0 && i != 0) {
				writeFile << std::endl;
			}
		}
	}
}

std::string TextFile::cleanWord(std::string & word, std::vector<std::string> & currWords) const {
	std::vector<int> del;
	std::string ret(word);
	for (unsigned int i = 0; i < ret.size(); ++i) {
		for (unsigned int j = 0; j < delPunctList.size(); ++j) {
			if (delPunctList[j] == ret[i]) {
				del.push_back(i);
			}
		}
		for (unsigned int j = 0; j < replacePunctList.size(); ++j) {
			if (replacePunctList[j] == ret[i]) {
				ret[i] = '_';
			}
		}
	}

	for (unsigned int i = 0; i < del.size(); ++i) {
		ret.erase(del[i] - i, 1);
	}

	for (unsigned int i = 0; i < keyWords.size(); ++i) {
		if (ret == keyWords[i]) {
			ret += "_";
			break;
		}
	}

	while(GeneralFile::duplicateWord(ret, currWords)) {
		ret += "_";
	}
	return ret;
}

bool TextFile::isWord(std::string & word) const {
	bool found;
	for (unsigned int i = 0; i < replacePunctList.size(); ++i) {
		found = false; 
		for (unsigned int j = 0; j < word.size(); ++j) {
			if (word[j] == replacePunctList[i]) {
				found = true;
			}
		}
		if (found == false) {
			return true;
		}
	}
	return false;
}

TextFile::TextFile(const char* fileName) : GeneralFile(fileName), delPunctList("!.,*@#$&()^+~/|\\?<>;:[]{}—"), replacePunctList("-~'\'\"") {
	keyWords.push_back("alignas");
	keyWords.push_back("alignof");
	keyWords.push_back("and");
	keyWords.push_back("and_eq");
	keyWords.push_back("asm");
	keyWords.push_back("auto");
	keyWords.push_back("bitand");
	keyWords.push_back("bitor");
	keyWords.push_back("bool");
	keyWords.push_back("break");
	keyWords.push_back("case");
	keyWords.push_back("catch");
	keyWords.push_back("char");
	keyWords.push_back("char16_t");
	keyWords.push_back("char32_t");
	keyWords.push_back("class");
	keyWords.push_back("compl");
	keyWords.push_back("const");
	keyWords.push_back("constexpr");
	keyWords.push_back("const_cast");
	keyWords.push_back("continue");
	keyWords.push_back("decltype");
	keyWords.push_back("default");
	keyWords.push_back("delete");
	keyWords.push_back("do");
	keyWords.push_back("double");
	keyWords.push_back("dynamic_cast");
	keyWords.push_back("else");
	keyWords.push_back("enum");
	keyWords.push_back("explicit");
	keyWords.push_back("export");
	keyWords.push_back("extern");
	keyWords.push_back("false");
	keyWords.push_back("float");
	keyWords.push_back("for");
	keyWords.push_back("friend");
	keyWords.push_back("goto");
	keyWords.push_back("if");
	keyWords.push_back("inline");
	keyWords.push_back("int");
	keyWords.push_back("long");
	keyWords.push_back("mutable");
	keyWords.push_back("namespace");
	keyWords.push_back("new");
	keyWords.push_back("noexcept");
	keyWords.push_back("not");
	keyWords.push_back("not_eq");
	keyWords.push_back("nullptr");
	keyWords.push_back("operator");
	keyWords.push_back("or");
	keyWords.push_back("or_eq");
	keyWords.push_back("private");
	keyWords.push_back("protected");
	keyWords.push_back("public");
	keyWords.push_back("register");
	keyWords.push_back("reinterpret_cast");
	keyWords.push_back("return");
	keyWords.push_back("short");
	keyWords.push_back("signed");
	keyWords.push_back("sizeof");
	keyWords.push_back("static");
	keyWords.push_back("static_assert");
	keyWords.push_back("static_cast");
	keyWords.push_back("struct");
	keyWords.push_back("switch");
	keyWords.push_back("template");
	keyWords.push_back("this");
	keyWords.push_back("thread_local");
	keyWords.push_back("throw");
	keyWords.push_back("true");
	keyWords.push_back("try");
	keyWords.push_back("typedef");
	keyWords.push_back("typeid");
	keyWords.push_back("typename");
	keyWords.push_back("union");
	keyWords.push_back("unsigned");
	keyWords.push_back("using");
	keyWords.push_back("virtual");
	keyWords.push_back("void");
	keyWords.push_back("volatile");
	keyWords.push_back("wchar_t");
	keyWords.push_back("while");
	keyWords.push_back("xor");
	keyWords.push_back("xor_eq");
}


void TextFile::parse() {
	if (!isOpen()) {
		throw FileNotOpen();
	}

	std::string temp;
	while (!fileStream.eof()) {
		fileStream >> temp;
		temp = cleanWord(temp, parsedFile);
		if (TextFile::isWord(temp)) {
			parsedFile.push_back(temp);
		}
	}
	isParsed = true;
	closeFile();
}

bool ProgramFile::quotesPaired(const std::string & word) {
	int count = 0;
	int count2 = 0;
	for (unsigned int i = 0; i < word.size(); ++i) {
		if (word[i] == '\"') {
			++count;
		} else if (word[i] == '\'') {
			++count2;
		}

	}
	return (count % 2 == 0 && count % 2 == 0);
}

void ProgramFile::preprocess() {
	// intermediary filestream to create a processed program file without comments and #include's
	std::ofstream tempFile;
	tempFile.open(tempFileName);

	// vector of strings to store lines of code
	std::vector<std::string> lines;

	// string for temporary storage and manipulation
	std::string tempLine;

	// reading in program file into lines
	while (!fileStream.eof()) {
		getline(fileStream, tempLine);
		lines.push_back(tempLine);
	}

	size_t temp;
	for (unsigned int i = 0; i < lines.size(); ++i) {
		// finding line comments
		temp = lines[i].find("//");
		while (temp != std::string::npos) {
			lines[i].erase(temp, lines[i].size());
			temp = lines[i].find("//");
		}

		// finding block comments
		temp = lines[i].find("/*"); // won't find nested block comments
		if (temp != std::string::npos) {
			size_t temp2;
			temp2 = lines[i].find("*/");

			// need j so that we save the initial position of i
			int j = 0;
			while (temp2 == std::string::npos) {
				if (j != 0) {
					lines[i + j].erase(0, lines[i + j].size());
				} else {
					lines[i].erase(temp, lines[i].size());
				}
				++j;
				temp2 = lines[i + j].find("*/");
			}

			if (j == 0) {
				lines[i].erase(temp, temp2 - temp + 2);
			} else {
				lines[i + j].erase(0, temp2 + 2);
			}
		}

		// finding #includes
		temp = lines[i].find("#include");
		if (temp != std::string::npos) {
			includes.push_back(lines[i]);
		} else {
			// writing lines to out file if it is not empty
			if (lines[i] != "") {
				tempFile << lines[i] << std::endl;
			}
		}
	}

	tempFile.close();
}


ProgramFile::ProgramFile(const char* fileName) : GeneralFile(fileName), tempFileName("temp.temp") { }

void ProgramFile::parse() {
	preprocess();

	std::string temp;
	std::string builder;

	// opens temporary file for reading
	std::ifstream file(tempFileName);

	while (!file.eof()) {
		file >> temp;

		// if begining of qoute, continue to attach words until end of quotes are found.
		if (temp.find("\"") != std::string::npos) {
			while (!quotesPaired(temp)) {
				file >> builder;
				temp += " " + builder;
			}
		}
		parsedFile.push_back(temp);
	}
	parsedFile.pop_back();
	file.close();
	isParsed = true;
	// remove(tempFile);
}

// new version of preprocess not done yet
void preprocess_new() { 
	// intermediary filestream to create a processed program file without comments and #include's
	std::ofstream tempFile;
	tempFile.open(tempFileName);

	// vector of strings to store lines of code
	std::vector<std::string> lines;

	// string for temporary storage and manipulation
	std::string tempLine;

	
}