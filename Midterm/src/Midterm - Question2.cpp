#include <iostream>
#include <string>
#include <memory>
using namespace std;

class UHKClass {
public:
	UHKClass() {}
};

int main() {
	// Instatiate one instance of the class
	shared_ptr<UHKClass> initialUHKClass;

	// Instantiate 20 instances of the class and put in array
	shared_ptr<UHKClass> arrayClass1;
	shared_ptr<UHKClass> arrayClass2;
	shared_ptr<UHKClass> arrayClass3;
	shared_ptr<UHKClass> arrayClass4;
	shared_ptr<UHKClass> arrayClass5;
	shared_ptr<UHKClass> arrayClass6;
	shared_ptr<UHKClass> arrayClass7;
	shared_ptr<UHKClass> arrayClass8;
	shared_ptr<UHKClass> arrayClass9;
	shared_ptr<UHKClass> arrayClass10;
	shared_ptr<UHKClass> arrayClass11;
	shared_ptr<UHKClass> arrayClass12;
	shared_ptr<UHKClass> arrayClass13;
	shared_ptr<UHKClass> arrayClass14;
	shared_ptr<UHKClass> arrayClass15;
	shared_ptr<UHKClass> arrayClass16;
	shared_ptr<UHKClass> arrayClass17;
	shared_ptr<UHKClass> arrayClass18;
	shared_ptr<UHKClass> arrayClass19;
	shared_ptr<UHKClass> arrayClass20;

	shared_ptr<UHKClass> classArray[20] = {
			arrayClass1,
			arrayClass2,
			arrayClass3,
			arrayClass4,
			arrayClass5,
			arrayClass6,
			arrayClass7,
			arrayClass8,
			arrayClass9,
			arrayClass10,
			arrayClass11,
			arrayClass12,
			arrayClass13,
			arrayClass14,
			arrayClass15,
			arrayClass16,
			arrayClass17,
			arrayClass18,
			arrayClass19,
			arrayClass20
	};

	// Return all instances to the system
	initialUHKClass = nullptr;
	for(int i = 0; i < 20; i++) {
		classArray[i] = nullptr;
	}

	return EXIT_SUCCESS;
}
