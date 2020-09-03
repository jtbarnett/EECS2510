// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Homework 0 - Part C

#include <iostream>
#include <fstream>
using namespace std;

int getNumberOfRuns(int array[], int sizeOfArray);

int main(int argCount, char *argValues[]) {
	ifstream inFile;
	// CHANGE THE TEST FILE HERE
	inFile.open("src\\testdata.txt");

	if (!inFile.is_open()) {
		cerr << "Error while opening the file" << endl;
		exit(EXIT_FAILURE);
	} else {
		// Get the length of the file so we can set the length of the data array
		string numberList;
		int lengthOfFile;
		int currentInt;

		while (inFile >> currentInt) {
			numberList.append(to_string(currentInt));
			lengthOfFile++;
		}

		// Store the data into the data array
		int data[lengthOfFile];
		for (int i = 0; i < lengthOfFile; i++) {
			char dataToInput = numberList[i];
			dataToInput = dataToInput - '0';
			data[i] = dataToInput;
		}

		// Call the method that returns the number of runs in the array
		int numberOfRuns = getNumberOfRuns(data, lengthOfFile);
		cout << "The total number of runs in the array: " << numberOfRuns << endl;
		inFile.close();
	}
	return EXIT_SUCCESS;
}

int getNumberOfRuns(int inputArray[], int sizeOfArray) {
	// Only want to make a run when the run changes to a different value
	int runs = 0;
	int previousValue, currentValue;
	bool isUpRun = false;
	bool isDownRun = false;
	bool upOrDownRun = false;

	for (int i = 0; i < sizeOfArray; i++) {
		if (i != 0) {
			currentValue = inputArray[i];

			// Case when we are looking at the second item and don't have any run bool's set
			if (i == 1) {
				if (currentValue > previousValue) {
					isUpRun = true;
				} else if (currentValue < previousValue){
					isDownRun = true;
				} else {
					upOrDownRun = true;
				}
			} else if (i == sizeOfArray - 1) {
				// Check at the end of the array
				if (isUpRun) {
					if (currentValue < previousValue) {
						runs += 2;
					} else {
						runs++;
					}
				} else if (isDownRun) {
					if (currentValue > previousValue) {
						runs += 2;
					} else {
						runs++;
					}
				} else {
					runs++;
				}
			} else {
				// Check to see if we don't know if it will be an up or down run yet
				if (upOrDownRun) {
					if (currentValue > previousValue) {
						isUpRun = true;
						upOrDownRun = false;
					} else if (currentValue < previousValue){
						isDownRun = true;
						upOrDownRun = false;
					}
				} else if (isUpRun) {
					// Main check for up run
					if (currentValue < previousValue) {
						runs++;
						isUpRun = false;
						isDownRun = true;
						upOrDownRun = false;
					}
				} else if (isDownRun) {
					// Main check for down run
					if (currentValue > previousValue) {
						runs++;
						isDownRun = false;
						isUpRun = true;
						upOrDownRun = false;
					}
				}
			}
		}
		previousValue = inputArray[i];
	}
	return runs;
}





/*
int getNumberOfRuns(int inputArray[], int sizeOfArray) {
	// Only want to make a run when the run changes to a different value
	int runs = 0;
	int previousValue, currentValue;
	bool isUpRun = false;
	bool isDownRun = false;
	bool upOrDownRun = false;

	for (int i = 0; i < sizeOfArray; i++) {
		if (i != 0) {
			currentValue = inputArray[i];

			// Case when we are looking at the second item and don't have any run bool's set
			if (i == 1) {
				if (currentValue > previousValue) {
					isUpRun = true;
				} else if (currentValue < previousValue){
					isDownRun = true;
				} else {
					upOrDownRun = true;
				}
			} else if (i == sizeOfArray - 1) {
				if (isUpRun || isDownRun || upOrDownRun) {
					runs++;
				}
			} else {
				// Check to see if we are continuing whether we don't know if it will be an up or down run yet
				if (upOrDownRun) {
					if (currentValue > previousValue) {
						isUpRun = true;
						upOrDownRun = false;
					} else if (currentValue < previousValue){
						isDownRun = true;
						upOrDownRun = false;
					}
				} else {
					// Main check for up run
					if (isUpRun) {
						if (currentValue < previousValue) {
							runs++;
							isUpRun = false;
							isDownRun = true;
							upOrDownRun = false;
						}
					} else if (isDownRun) {
					// Main check for down run
						if (currentValue > previousValue) {
							runs++;
							isDownRun = false;
							isUpRun = true;
							upOrDownRun = false;
						}
					} else {
					// Check if down and up is false
						if (currentValue > previousValue) {
							isUpRun = true;
						} else if (currentValue < previousValue) {
							isDownRun = true;
						} else {
							upOrDownRun = true;
						}
					}
				}
			}
		}
		previousValue = inputArray[i];
	}
	return runs;
}*/




