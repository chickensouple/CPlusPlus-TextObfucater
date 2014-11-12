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

// main func
int main() {
	orange myOrange; int i = 2;
	myOrange.weight = 2.1;
	myOrange.name = "greg"; /// his name is greg

	cout << myOrange.name << " is " << myOrange.weight << "lbs\n";
}
