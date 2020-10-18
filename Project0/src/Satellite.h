// Jacob Barnett
// EECS 2510 Non-Linear Data Structures
// Project 0

#ifndef __SATELLITE_H__
#define __SATELLITE_H__

#include <iostream>
#include <string>
using namespace std;

struct Satellite {
	string name;
	string country;
	string nameOfOperator;
	string type;
	string purpose;
	string detailedPurpose;
	string orbitType;
	int apogee;
	int perigee;
	float period;
	string date;
	string expectedLifetime;
	string launchSite;
	string launchVehicle;
	int noradNumber;
};

#endif
