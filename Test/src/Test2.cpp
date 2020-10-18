#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream inFile;
	int firstValue, nbrValuesRead = 0;
	int fileContents[10000];

	inFile.open("testdata.txt");
	if (!inFile.is_open()) {
		cerr << "Couldn't open \"testdata.txt\"" << endl;
		return !0;
	}
	inFile >> firstValue;
	while (inFile.good() && !inFile.eof()) {
		cout << "Read in : " << firstValue << endl;
		fileContents[nbrValuesRead] = firstValue;
		nbrValuesRead++;
		inFile >> firstValue;
	}
	inFile.close( );
    for (int i = 0; i < nbrValuesRead; i++) {
    	cout << "fileContents[" << i <<"] = " << fileContents[i] << endl;
    }
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}

