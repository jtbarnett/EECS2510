// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 0

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "operations.h"
#include "SatelliteTree.h"
#include "Satellite.h"
using namespace std;

int main(int argCount, char *argValues[]) {
	shared_ptr<SatelliteTree> satTree(new SatelliteTree());
	shared_ptr<SatelliteTree> deorbTree(new SatelliteTree());

	// Load in the initial data into the satellite tree
	ifstream inFile;
	inFile.open("Dataset1.txt");
	if (!inFile.is_open()){
		cerr << "Error while opening the file Dataset1.txt." << endl;
		exit(EXIT_FAILURE);
	} else {
		operations::inputSatellites(inFile, satTree);
		inFile.close();
	}

	cout << "The commands to enter are: L or l (launch a new satellite), F or f (search for a satellite), D or d (deorbit a satellite), \n"
			"A or a (list all satellites), S or s (save all satellites), R or r (read saved satellites), Q or q (quit the program)" << endl;

	string input;
	while (true) {
		cout << "\nEnter a command (L-launch, F-find, D-deorbit, A-list all, S-save, R-read, Q-quit): ";
		getline(cin, input);

		if (input == "L" || input == "l") {
			operations::launch(satTree);
		} else if (input == "F" || input == "f") {
			operations::find(satTree, deorbTree);
		} else if (input == "D" || input == "d") {
			operations::deorbit(satTree, deorbTree);
		} else if (input == "A" || input == "a") {
			operations::listAll(satTree, deorbTree);
		} else if (input == "S" || input == "s") {
			operations::save(satTree, deorbTree);
		} else if (input == "R" || input == "r") {
			satTree->deleteTree(satTree->root);
			satTree->deleteRoot();
			deorbTree->deleteTree(deorbTree->root);
			deorbTree->deleteRoot();
			operations::read(satTree, deorbTree);
		} else if (input == "Q" || input == "q") {
			cout << "You have exited the program." << endl;
			break;
		} else {
			cout << "You have entered an invalid command. Please try again." << endl;
		}
	}
	return EXIT_SUCCESS;
}
