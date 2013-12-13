/*
Story code transformer!
takes a c++ code and a .txt file, and creates a file that #defines all of the story words 
and writes out the story such that it will be your original c++ code but in the form of a story.
note: this program is a work in progress and far from perfect, if your program is using some c++ keywords in strings or 
other random things this may not work and could require a little hand tweaking
Only works for c++ code.
make sure all your #include's are on separate lines

syntax from command line is program_literature <name of .cpp file> <name of text file> <name of output file>
author: clark zhang
last updated: 12/12/2013
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// TODO:
// nested block comments will cause errors
// get #includes that are not on its own line
// ignore #includes in quotes
// make string comparisons case insensitive
// add command line options

// number of words per line to write to output file
const int wordsPerLine = 15;

// list of punctuation to ignore in the text file
const string punctuationList = "!.,*@#$&()-^+~`/|\\?><;:\'\"[]{}—";

// list of punctuation that can be removed
const string delPunctList = "!.,*@#$&()^+~/|\\?<>;:[]{}—";

// list of punctuation that can be replaced by underscore
const string replacePunctList = "-~'\'\"";

// name of the intermediary file
const char* tempFileName = "temp.temp";

// array of c++ key words
const string keyWords[] = {"alignas",
"alignof",
"and",
"and_eq",
"asm",
"auto",
"bitand",
"bitor",
"bool",
"break",
"case",
"catch",
"char",
"char16_t",
"char32_t",
"class",
"compl",
"const",
"constexpr",
"const_cast",
"continue",
"decltype",
"default",
"delete",
"do",
"double",
"dynamic_cast",
"else",
"enum",
"explicit",
"export",
"extern",
"false",
"float",
"for",
"friend",
"goto",
"if",
"inline",
"int",
"long",
"mutable",
"namespace",
"new",
"noexcept",
"not",
"not_eq",
"nullptr",
"operator",
"or",
"or_eq",
"private",
"protected",
"public",
"register",
"reinterpret_cast",
"return",
"short",
"signed",
"sizeof",
"static",
"static_assert",
"static_cast",
"struct",
"switch",
"template",
"this",
"thread_local",
"throw",
"true",
"try",
"typedef",
"typeid",
"typename",
"union",
"unsigned",
"using",
"virtual",
"void",
"volatile",
"wchar_t",
"while",
"xor",
"xor_eq"};

// vector of c++ keywords
const vector<string> keyWordsList (keyWords, keyWords + sizeof(keyWords) / sizeof(string));

// takes a program file and removes the #include's and comments, returns a list of the #includes
vector<string> preprocessFile(ifstream & inFile, ofstream & outFile);

// takes a file and parses it into a vector of strings as well as cleaning each word
vector<string> parseTextFile(ifstream & file);

// takes a file and parses it into a vector of strings, keeps quotes in one string
vector<string> parseProgramFile(ifstream & file);

// cleans word of punctuation
string cleanWord(string & word, const vector<string> & currWords);

// cleans sentence of extraneous underscores
string cleanSentence(string & sentence, const vector<string> & currSentences);

// checks it word is a duplicate of something in currWords
bool duplicateWord(string & word, const vector<string> & currWords);

// checks if the word has an even number of quotes
bool quotesPaired(const string & word);

// creates the output file
void createFile(vector<string> & programWords, vector<string> & textWords, ofstream & writeFile);

int main(int argc, char *argv[]) {
	if (argc != 4) {
		cout << "Invalid arguments";
		return 1;
	}
	ifstream programf(argv[1]); // for reading in program file
	ifstream textFilef(argv[2]); // for reading in text file
	ofstream writeFile(argv[3]); // for writing to a different .cpp file
	ofstream tempFile(tempFileName); // temp file for processing program file
	vector<string> programWords;
	vector<string> textWords;
	vector<string> includes;

	// processing program file into temp file
	if (programf.is_open()) {
		cout << "program file is open\n";
		includes = preprocessFile(programf, tempFile);
		cout << "processed program file\n";
	} else {
		cout << "unable to open program file. abort.\n";
		return 1;
	}
	

	// writing the includes to top of file
	for (unsigned int i = 0; i < includes.size(); ++i) {
		writeFile << includes[i] << endl;
	}
	writeFile << "\n\n";

	// closing files
	programf.close();
	tempFile.close();
	cout << "program file is closed\n";

	// opening ifstream for the processed program file
	ifstream processedProgramf(tempFileName);

	if (processedProgramf.is_open()) {
		cout << "intermediary file is open\n";
		programWords = parseProgramFile(processedProgramf);
		cout << "parsed intermediary file\n";
		processedProgramf.close();
		cout << "intermediary file is closed\n";
	} else {
		cout << "unable to open intermediary file. abort.\n";
		return 1;
	}

	if (textFilef.is_open()) {
		cout << "textfile is open\n";
		textWords = parseTextFile(textFilef);
		cout << "parsed text file\n";
		textFilef.close();
		cout << "text file is closed\n";
	} else {
		cout << "unable to open text file. abort.\n";
		return 1;
	}

	createFile(programWords, textWords, writeFile);
	cout << "created new file\n";
	writeFile.close();

	remove(tempFileName);
	cout << "removed intermediary file\ndone.\n";
}

void createFile(vector<string> & programWords, vector<string> & textWords, ofstream & writeFile) {
	int ratio1 = programWords.size() / textWords.size();
	int ratio2 = textWords.size() / programWords.size();

	// if there are more words in program than in text
	if (ratio1 >= ratio2) {
		// writes the first textWords.size() - 1 #define's to file along (because the last one may have an irregular number of associated program words)
		for (unsigned int i = 0; i < textWords.size() - 1; ++i) {
			writeFile << "#define " << textWords[i] << " ";
			for (int j = 0; j < ratio1; ++j) {
				writeFile << programWords[ratio1 * i + j] << " ";
			}
			writeFile << endl;
		}

		// writing the last #define
		writeFile << "#define " << textWords[textWords.size() - 1] << " ";
		for (unsigned int i = (textWords.size() - 1) * ratio1; i < programWords.size(); ++i) {
			writeFile << programWords[i] << " ";
		}
		writeFile << "\n\n\n";

		// writing the textwords
		for (unsigned int i = 0; i < textWords.size(); ++i) {
			writeFile << textWords[i] << " ";
			if (i % wordsPerLine == 0 && i != 0) {
				writeFile << endl;
			}
		}
	} else {
	// if there are more words in text than in program

		//temp is for storing concatenated strings with the underscore
		vector<string> temp;

		//a string for building up a string concatenation
		string builder;

		// writing the first programWords.size() - 1 #define's
		for (unsigned int i = 0; i < programWords.size() - 1; ++i) {
			writeFile << "#define ";
			builder = "";
			for (int j = 0; j < ratio2; ++j) {
				if (j != ratio2 - 1) {
					builder += textWords[ratio2 * i + j] + "_";
				} else {
					builder += textWords[ratio2 * i + j];
				}
			}
			cleanSentence(builder, temp);
			temp.push_back(builder);
			writeFile << builder << " " << programWords[i] << endl;
		}

		// writing the last #define
		writeFile << "#define ";
		builder = "";
		for (unsigned int i = (programWords.size() - 1) * ratio2; i < textWords.size(); ++i) {
			if (i != textWords.size() - 1) {
				builder += textWords[i] + "_";
			} else {
				builder += textWords[i];
			}
		}
		cleanSentence(builder, temp);
		temp.push_back(builder);
		writeFile << builder << " " << programWords[programWords.size() - 1] << "\n\n\n";

		// writing out whatever is in temp
		for (unsigned int i = 0; i < temp.size(); ++i) {
			writeFile << temp[i] << " ";
			if (i % (wordsPerLine / ratio2) == 0 && i != 0) {
				writeFile << endl;
			}
		}

	}
}

vector<string> parseProgramFile(ifstream & file) {
	vector<string> ret;
	string temp;
	string builder;
	while (!file.eof()) {
		file >> temp;
		if (temp[0] == '\"') {
			do {
				file >> builder;
				temp += " " + builder;
			} while (!quotesPaired(temp));
		}
		ret.push_back(temp);
	}
	ret.pop_back();
	return ret;
}

vector<string> parseTextFile(ifstream & file) {
	vector<string> ret;
	string temp;
	while (!file.eof()) {
		file >> temp;
		cleanWord(temp, ret);
		ret.push_back(temp);
	}
	return ret;
}

string cleanWord(string & word, const vector<string> & currWords) {
	vector<int> del;
	for (unsigned int i = 0; i < word.size(); ++i) {
		for (unsigned int j = 0; j < delPunctList.size(); ++j) {
			if (delPunctList[j] == word[i]) {
				del.push_back(i);
				// word.erase(i, 1);
				// word[i] = '_';
			}
		}
		for (unsigned int j = 0; j < replacePunctList.size(); ++j) {
			if (replacePunctList[j] == word[i]) {
				word[i] = '_';
			}
		}
	}

	for (unsigned int i = 0; i < del.size(); ++i) {
		word.erase(del[i] - i, 1);
	}

	for (unsigned int i = 0; i < keyWordsList.size(); ++i) {
		if (word == keyWordsList[i]) {
			word += "_";
			break;
		}
	}

	while(duplicateWord(word, currWords)) {
		word += "_";
	}
	return word;
}

string cleanSentence(string & sentence, const vector<string> & currSentences) {
	vector<int> del;
	for (unsigned int i = 0; i < sentence.size(); ++i) {
		if (sentence[i] == '_') {
			if (i + 1 != sentence.size() && sentence[i + 1] == '_') {
				del.push_back(i + 1);
			}
		}
	}

	for (unsigned int i = 0; i < del.size(); ++i) {
		sentence.erase(del[i] - i, 1);
	}

	while(duplicateWord(sentence, currSentences)) {
		sentence += "_";
	}

	return sentence;
}

bool duplicateWord(string & word, const vector<string> & currWords) {
	for (unsigned int i = 0; i < currWords.size(); ++i) {
		if (word == currWords[i]) {
			return true;
		}
	}
	return false;
}

bool quotesPaired(const string & word) {
	int count = 0;
	for (unsigned int i = 0; i < word.size(); ++i) {
		if (word[i] == '\"') {
			++count;
		}
	}
	return (count % 2 == 0);
}

vector<string> preprocessFile(ifstream & inFile, ofstream & outFile) {
	vector<string> lines;
	vector<string> includes;
	string tempLine;
	while (!inFile.eof()) {
		getline(inFile, tempLine);
		lines.push_back(tempLine);
	}

	size_t temp;
	for (unsigned int i = 0; i < lines.size(); ++i) {
		// finding line comments
		temp = lines[i].find("//");
		while (temp != string::npos) {
			lines[i].erase(temp, lines[i].size());
			temp = lines[i].find("//");
		}

		// finding block comments
		temp = lines[i].find("/*"); // won't find nested block comments
		if (temp != string::npos) {
			size_t temp2;
			temp2 = lines[i].find("*/");

			// need j so that we save the initial position of i
			int j = 0;
			while (temp2 == string::npos) {
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
				lines[i + j].erase(0, temp2 + 3);
			}
		}

		// finding #includes
		temp = lines[i].find("#include");
		if (temp != string::npos) {
			includes.push_back(lines[i]);
		} else {
			// writing lines to out file if it is not empty
			if (lines[i] != "") {
				outFile << lines[i] << endl;
			}
		}
	}
	return includes;
}