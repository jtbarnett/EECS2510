// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 0

#ifndef __OPERATIONS_H__
#define __OPERATIONS_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "SatelliteTree.h"
#include "Satellite.h"
using namespace std;

/*
 * This file is used for operations such as loading in the inital satellite data, launch,
 * find, deorbit, list all, save, read
 */
namespace operations {
	void inputSatellites(ifstream& inFile, shared_ptr<SatelliteTree> inputTree);
	void listNodeData(ostream& ostr, shared_ptr<SatelliteTree::Node> inputNode);
	void launch(shared_ptr<SatelliteTree> satelliteTree);
	void find(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree);
	void deorbit(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree);
	void listAll(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree);
	void save(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree);
	void read(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree);

	void launch(shared_ptr<SatelliteTree> satelliteTree) {
		Satellite satellite;
		string input;

		cout << "You are launching a new satellite. Please specify the data fields below." << endl;
		// get name
		cout << "enter the satellite's name: ";
		getline(cin, input);
		satellite.name = input;
		// get country
		cout << "enter the satellite's country: ";
		getline(cin, input);
		satellite.country = input;
		// get name of operator
		cout << "enter the name of operator: ";
		getline(cin, input);
		satellite.nameOfOperator = input;
		// get type of satellite
		cout << "enter the type of satellite: ";
		getline(cin, input);
		satellite.type = input;
		// get purpose
		cout << "enter the satellite's purpose: ";
		getline(cin, input);
		satellite.purpose = input;
		// get detailed purpose
		cout << "enter the satellite's detailed purpose: ";
		getline(cin, input);
		satellite.detailedPurpose = input;
		// get orbit type
		cout << "enter the orbit type: ";
		getline(cin, input);
		satellite.orbitType = input;
		// get apogee
		cout << "enter the apogee (number): ";
		getline(cin, input);
		stringstream stringToInt(input);
		stringToInt >> satellite.apogee;
		// get perigee
		cout << "enter the perigee (number): ";
		getline(cin, input);
		stringstream stringToIntPerigee(input);
		stringToIntPerigee >> satellite.perigee;
		// get period
		cout << "enter the period (number): ";
		getline(cin, input);
		try {
			satellite.period = stof(input);
		} catch (const std::invalid_argument& e) {
			satellite.period = 0;
		}
		// get date of launch
		cout << "enter the date of launch: ";
		getline(cin, input);
		satellite.date = input;
		// get expected lifetime
		cout << "enter the expected liftime (in years): ";
		getline(cin, input);
		satellite.expectedLifetime = input;
		// get launch site
		cout << "enter the launch site: ";
		getline(cin, input);
		satellite.launchSite = input;
		// get launch vehicle
		cout << "enter the launch vehicle: ";
		getline(cin, input);
		satellite.launchVehicle = input;
		// get norad tracking number
		cout << "enter the norad tracking number: ";
		getline(cin, input);
		stringstream stringToIntNorad(input);
		stringToIntNorad >> satellite.noradNumber;

		satelliteTree->insert(satellite);
	}

	void find(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree) {
		string input;
		cout << "Enter the name of the satellite that you are trying to find: ";
		getline(cin, input);
		shared_ptr<SatelliteTree::Node> nodeSatelliteTree = satelliteTree->find(input);
		if (nodeSatelliteTree == nullptr) {
			shared_ptr<SatelliteTree::Node> nodeDeorbitTree = deorbitTree->find(input);
			if (nodeDeorbitTree == nullptr) {
				cout << "Sorry, the satellite could not be found." << endl;
			} else {
				cout << "\nThe satellite was found, but it has been deorbited." << endl;
				listNodeData(cout, nodeDeorbitTree);
			}
		} else {
			cout << "\nThe satellite was found and it is in orbit." << endl;
			listNodeData(cout, nodeSatelliteTree);
		}
	}

	void deorbit(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree) {
		string input;
		cout << "Enter the name of the satellite that you want to deorbit: ";
		getline(cin, input);
		shared_ptr<SatelliteTree::Node> returnNode = satelliteTree->find(input);
		if (returnNode == nullptr){
			cout << "Sorry, the satellite you are trying to deorbit could not be found." << endl;
		} else {
			cout << "The satellite " << input << " has been successfully deorbited." << endl;
			deorbitTree->insert(returnNode->satellite);
			satelliteTree->deleteNode(returnNode);
		}
	}

	void listAll(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree) {
		cout << "Satellites in orbit:" << endl;
		satelliteTree->inOrder();
		cout << "\nSatellites that have been deorbited:" << endl;
		deorbitTree->inOrder();
	}

	void save(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree) {
		ofstream outFile;

		// Output inorbit tree to inorbit.txt
		outFile.open("inorbit.txt");
		if (!outFile.is_open()){
			cerr << "Error while opening the file inorbit.txt." << endl;
			exit(EXIT_FAILURE);
		} else {
			satelliteTree->preOrder(outFile);
		}
		outFile.close();

		// Output deorbit tree to deorbit.txt
		outFile.open("deorbit.txt");
		if (!outFile.is_open()){
			cerr << "Error while opening the file deorbit.txt." << endl;
			exit(EXIT_FAILURE);
		} else {
			deorbitTree->preOrder(outFile);
		}
		outFile.close();

		cout << "You have successfully saved all satellite information." << endl;
	}

	void read(shared_ptr<SatelliteTree> satelliteTree, shared_ptr<SatelliteTree> deorbitTree) {
		ifstream inFile;
		// Read in the inorbit.txt file to the inorbit tree
		inFile.open("inorbit.txt");
		if (!inFile.is_open()){
			cerr << "Error while opening the file inorbit.txt." << endl;
			exit(EXIT_FAILURE);
		} else {
			inputSatellites(inFile, satelliteTree);
			inFile.close();
		}
		// Read in the deorbit.txt file to the deorbit tree
		inFile.open("deorbit.txt");
		if (!inFile.is_open()){
			cerr << "Error while opening the file deorbit.txt." << endl;
			exit(EXIT_FAILURE);
		} else {
			inputSatellites(inFile, deorbitTree);
			inFile.close();
		}
		cout << "You have successfully read in all satellite information." << endl;
	}

	void listNodeData(ostream& ostr, shared_ptr<SatelliteTree::Node> inputNode) {
		ostr << "Name: " << inputNode->satellite.name << endl;
		ostr << "Country: " << inputNode->satellite.country << endl;
		ostr << "Name of operator: " << inputNode->satellite.nameOfOperator << endl;
		ostr << "Type: " << inputNode->satellite.type << endl;
		ostr << "Purpose: " << inputNode->satellite.purpose << endl;
		ostr << "Detailed purpose: " << inputNode->satellite.detailedPurpose << endl;
		ostr << "Orbit type: " << inputNode->satellite.orbitType << endl;
		ostr << "Apogee: " << inputNode->satellite.apogee << endl;
		ostr << "Perigee: " << inputNode->satellite.perigee << endl;
		ostr << "Period: " << inputNode->satellite.period << endl;
		ostr << "Date of launch: " << inputNode->satellite.date << endl;
		ostr << "Expected lifetime: " << inputNode->satellite.expectedLifetime << endl;
		ostr << "Launch site: " << inputNode->satellite.launchSite << endl;
		ostr << "Launch vehicle: " << inputNode->satellite.launchVehicle << endl;
		ostr << "Norad tracking number: " << inputNode->satellite.noradNumber << endl;
	}

	void inputSatellites(ifstream& inFile, shared_ptr<SatelliteTree> inputTree) {
		string junk;
		Satellite satellite;
		while (inFile.good() && !inFile.eof()) {
			getline(inFile, satellite.name);
			if (inFile.bad() || inFile.eof()) {
				break;
			}
			getline(inFile, satellite.country);
			getline(inFile, satellite.nameOfOperator);
			getline(inFile, satellite.type);
			getline(inFile, satellite.purpose);
			getline(inFile, satellite.detailedPurpose);
			getline(inFile, satellite.orbitType);
			inFile >> satellite.apogee >> satellite.perigee >> satellite.period;
			getline(inFile, junk);
			getline(inFile, satellite.date);
			getline(inFile, satellite.expectedLifetime);
			getline(inFile, satellite.launchSite);
			getline(inFile, satellite.launchVehicle);
			inFile >> satellite.noradNumber;
			getline(inFile, junk);

			// Input the satellite into the tree
			inputTree->insert(satellite);
		}
	}
}

#endif
