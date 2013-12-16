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
last updated: 12/15/2013
*/

#include "fileClasses.h"

// TODO:
// nested block comments will cause errors
// get #includes that are not on its own line
// ignore #includes in quotes
// make string comparisons case insensitive
// add command line options
// search through program file to find function, variable, class, enum, etc. names
// generalize for other programming languages


int main(int argc, char *argv[]) {
	if (argc != 4) {
		std::cout << "invalid arguments";
		return 1;
	}
	ProgramFile program(argv[1]);
	TextFile text(argv[2]);
	text.parse();
	std::cout<< "parsed text.\n";
	program.parse();
	std::cout << "parsed program.\n";
	GeneralFile::createStoryFile(program, text, argv[3], 15);
	std::cout << "created file.\n";
	std::cout << "done.\n";
}