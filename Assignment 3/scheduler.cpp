// Author: Bader Abdulwaseem
// UCID: 30023849
// CPSC 457
// Question 7
// compile with: $ g++ count.cpp -O2 -o count.out -lm -lpthread

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;


struct processData {
	int arrivalTime;
	int burstTime;
	float waitingTime;
};

// Function taken from conrjac from GitHub.com
// Modifed slightly by me
// https://gist.github.com/conrjac/5387376
vector<string> stringSplit(string str, char delim) {
	istringstream ss(str);
	string token;
	vector<string> words;

	while(getline(ss, token, delim)) {
		words.push_back(token);
	}

    return words;
}

void shortestJobFirst() {}

void roundRobin() {}

int main(int argc, const char * argv[]) {

    // Exiting program if there is an invalid number of arguments
    if (argc < 3 || argc > 4) {
        cerr << "ERROR: Wrong Arguments\nCorrect useage: ./scheduler.out <file> <algorithm> <time-slice>" << endl;
        return -1;
    }

    string fileName = string(argv[1]);
    string algorithm = string(argv[2]);

	// This checks the command line input and error checks it. If everything is
	// correct, it will run the specified algorithm.
	if ((algorithm == "SJF" || algorithm == "sjf") && argc == 4) {
		cerr << "ERROR: Can't use time-slice with SJF" << endl;
		return -1;
	}
	else if ((algorithm == "SJF" || algorithm == "sjf") && argc == 3) {
		shortestJobFirst();
	}
	else if ((algorithm == "RR" || algorithm == "rr") && argc != 4) {
		cerr << "ERROR: RR must have a time-slice argument." << endl;
	}
	else if ((algorithm == "RR" || algorithm == "rr") && argc == 4) {
		roundRobin();
	}
	else {
		cerr << "Abort: the " << algorithm << " algorithm does not exist." << endl;
		return -1;
	}

    return 0;
}
