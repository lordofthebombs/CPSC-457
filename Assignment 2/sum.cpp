#include <iostream>
#include <vector>
#include <fstream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]) {

	// Checks to see if the program is being run with the correct inputs
	if (argc != 3) {
		cout << "This program takes two arguments in this format: 'input' 'thread count'" << endl;
		return 1;
	}

	// Converting the string into integer
	int numberOfThreads = stoi(argv[2]);

	vector<int> numbersFromInput;



	return 0;
}
