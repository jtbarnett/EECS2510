#ifndef __DISK_H__
#define __DISK_H__
#include <vector>
#include <iostream>
using namespace std;

template <class T>
class Disk {
private:
	vector<T>* diskblocks;
	vector<int> freeBlocks;
	int readCount, writeCount;
protected:
public:
	Disk() {
		diskblocks = new vector<T>();
		readCount = 0;
		writeCount = 0;
	}
	~Disk() {
		cerr << "Number of Blocks Read : " << readCount << endl;
		cerr << "Number of Blocks Written: " << writeCount << endl;
		delete diskblocks;
	}

	int getNumberOfBlocksRead() {
		return readCount;
	}

	int getNumberOfBlocksWritten() {
		return writeCount;
	}

	void writeBlock(int i, T block) {
		if (i < 0 || i >= int((*diskblocks).size())) {
			cerr << "Invalid address in writeBlock -- Address = " << i << endl;
			cerr << "Block not written." << endl;
			return;
		}
		(*diskblocks)[i] = block;
		writeCount++;
	}

	T readBlock(int i) {
		if (i < 0 || i >= int((*diskblocks).size())) {
			cerr << "Invalid address in readBlock -- Address = " << i << endl;
			cerr << "Block not written." << endl;
			return *(new T());
		}
		readCount++;
		return (*diskblocks)[i];
	}

	void createBlock(int t, bool leafValue, int a) {
		if (freeBlocks.size() == 0) {
			(*diskblocks).push_back(* new T(t, leafValue, a));
		}
		else {
			freeBlocks.pop_back();
		}
	}

	void returnBlock(int i) {
		if (i < 0 || i >(*diskblocks).size()) {
			cerr << "Invalid address in returnBlock -- Address = " << i << endl;
			cerr << "Block not added to freeBlocks" << endl;
		}
		else {
			freeBlocks.push_back(i);
		}
	}

};

#endif
