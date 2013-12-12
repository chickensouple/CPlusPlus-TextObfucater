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
last updated: 12/11/2013
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// TODO:
// allow option to delete punctuation rather than replace with underscore

const int wordsPerLine = 15;
const string punctuationList = "!.,*@#$&()-^+~`/|\\?><;:\'\"[]{}—";
const char* tempFileName = "temp.temp";
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

const vector<string> keyWordsList (keyWords, keyWords + sizeof(keyWords) / sizeof(string));

// takes a program file and removes the #include's and comments, returns a list of the #includes
vector<string> preprocessFile(ifstream & inFile, ofstream & outFile);

// takes a file and parses it into a vector of strings as well as cleaning each word
vector<string> parseTextFile(ifstream & file);

// takes a file and parses it into a vector of strings, keeps quotes in one string
vector<string> parseProgramFile(ifstream & file);

// cleans word of punctuation
void cleanWord(string & word, const vector<string> & currWords);

// checks it word is a duplicate of something in currWords
bool duplicateWord(string & word, const vector<string> & currWords);

// checks if the word has an even number of parantheses
bool parenthesesPaired(const string & word);

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
	for (int i = 0; i < includes.size(); ++i) {
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
		for (int i = 0; i < textWords.size() - 1; ++i) {
			writeFile << "#define " << textWords[i] << " ";
			for (int j = 0; j < ratio1; ++j) {
				writeFile << programWords[ratio1 * i + j] << " ";
			}
			writeFile << endl;
		}

		// writing the last #define
		writeFile << "#define " << textWords[textWords.size() - 1] << " ";
		for (int i = (textWords.size() - 1) * ratio1; i < programWords.size(); ++i) {
			writeFile << programWords[i] << " ";
		}
		writeFile << "\n\n\n";

		// writing the textwords
		for (int i = 0; i < textWords.size(); ++i) {
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
		for (int i = 0; i < programWords.size() - 1; ++i) {
			writeFile << "#define ";
			builder = "";
			for (int j = 0; j < ratio2; ++j) {
				if (j != ratio2 - 1) {
					builder += textWords[ratio2 * i + j] + "_";
				} else {
					builder += textWords[ratio2 * i + j];
				}
			}
			temp.push_back(builder);
			writeFile << builder << " " << programWords[i] << endl;
		}

		// writing the last #define
		writeFile << "#define ";
		builder = "";
		for (int i = (programWords.size() - 1) * ratio2; i < textWords.size(); ++i) {
			if (i != textWords.size() - 1) {
				builder += textWords[i] + "_";
			} else {
				builder += textWords[i];
			}
		}
		temp.push_back(builder);
		writeFile << builder << " " << programWords[programWords.size() - 1] << "\n\n\n";

		// writing out whatever is in temp
		for (int i = 0; i < temp.size(); ++i) {
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
			} while (!parenthesesPaired(temp));
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

void cleanWord(string & word, const vector<string> & currWords) {
	for (int i = 0; i < word.size(); ++i) {
		for (int j = 0; j < punctuationList.size(); ++j) {
			if (punctuationList[j] == word[i]) {
				// word.erase(i, 1);
				word[i] = '_';
				break;
			}
		}
	}
	for (int i = 0; i < keyWordsList.size(); ++i) {
		if (word == keyWordsList[i]) {
			word += "_";
			break;
		}
	}

	while(duplicateWord(word, currWords)) {
		word += "_";
	}

}

bool duplicateWord(string & word, const vector<string> & currWords) {
	for (int i = 0; i < currWords.size(); ++i) {
		if (word == currWords[i]) {
			return true;
		}
	}
	return false;
}

bool parenthesesPaired(const string & word) {
	int count = 0;
	for (int i = 0; i < word.size(); ++i) {
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
	for (int i = 0; i < lines.size(); ++i) {
		temp = lines[i].find("//");
		while (temp != string::npos) {
			lines[i].erase(temp, lines[i].size());
			temp = lines[i].find("//");
		}

		temp = lines[i].find("#include");
		if (temp != string::npos) {
			includes.push_back(lines[i]);
		} else {
			if (lines[i] != "") {
				outFile << lines[i] << endl;
			}
		}
	}
	return includes;
}