#include <iostream>
#define n newVar
using namespace std;

int* pascal(int n);

int main()
{
	int n;
	cout << "Row of Pascal numbers: ";
	cin >> n; /* 
	this is a block
	comment that spans
	several lines */int* line;
	line = pascal(n);
	for (int i = 0; i < (n+1); i++){
		cout << line[i] << "\t";
	}
	cout << "\n";
	delete [] line;
	return 0;
} 

int* pascal(int n){
	// int pointer to dynamically allocate arrays
	// for the last line of pascals and the current line
	int* line;
	int* previousline;
	line = new int[n+1];
	if (n == 0){
		// shouldn't here get here unless called with 0
		line[0] = 1;
		return line;
	} else if (n == 1){
		line[0] = 1;
		line[1] = 1;
		return line;
	} else{
		previousline = pascal(n - 1);
		for (int i = 1; i < (n + 1); i++){
			line[i] = previousline [i - 1] + previousline[i];
		}
		line[0] = 1;
		line[n] = 1;
		delete [] previousline;
		return line;
	}
}