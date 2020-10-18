#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Person {
private:
	string name;
	int age;
	float height;
	float weight;
public:
	// Class constructor
	Person(string inputName = "", int inputAge = 0, float inputHeight = 0, float inputWeight = 0) {
		name = inputName;
		age = inputAge;
		height = inputHeight;
		weight = inputWeight;
	}

	// Setters
	void setName(string input) {
		name = input;
	}

	void setAge(int input) {
		age = input;
	}

	void setHeight(float input) {
		height = input;
	}

	void setWeight(float input) {
		weight = input;
	}

	// Getters
	string getName() {
		return name;
	}

	int getAge() {
		return age;
	}

	float getHeight() {
		return height;
	}

	float getWeight() {
		return weight;
	}

	// Function for printing all of the Person's information
	void printInfo() {
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "Height:" << height << endl;
		cout << "Weight: " << weight << endl;
	}

	// Fucntion for calculating the Person's body mass index
	float getBodyMassIndex() {
		return (703 * weight) / pow(height, 2);
	}
};
