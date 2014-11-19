#include <iostream>
#include <stdint.h>
#include <string>
using namespace std;

struct orange {
	float weight;
	string name;
};

class apple {
	double weight;
	string name; /* this is a block
	comment that spans 
	multiple lines*/uint8_t color;
};

struct pear : public orange {
	string peariness;
};

void* myFunc() {}

double newFunc() {

} int globalvar = 5;

// main func
int main() {
	orange myOrange; int i = 2;
	int a, b, c;
	myOrange.weight = 2.1;
	myOrange.name = "greg multiword line so many words wow"; /// his name is greg
	string randomText = "blargl";
	string derp = "";
	int* robert;
	robert = new int[4];
	void* red = myFunc();

	cout << myOrange.name << " is " << myOrange.weight << "lbs\n";
}
