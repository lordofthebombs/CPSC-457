/*
Author: Bader Abdulwaseem
UCID: 30023849
Assignment 2
Question 3
*/


#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

define MAX_LEN 512

using namespace std;

int main(int argc, char *argv[]) {

    // Makes sure the right amount of arguments are typed in
    if (argc != 3) {
		cout << "This program takes two arguments in this format: 'extension' 'amount to list'." << endl;
		return 1;
	}

    int amountListed = stoi(argv[2]);
    vector<string> files;

    // Getting the data for find
    char fileNameBuffer[MAX_LEN];
    FILE *fp = popen("find . -type f", "r");
    if (!fp) {
        cerr << "popen() call failed." << endl;
        return -1;
    }

    // Storing each file into a vector
    while (fgets(fileNameBuffer, MAX_LEN, fp)) {
        files.push_back(string(fileNameBuffer));
    }

    for (int i = 0; i < files.size(); i++) {
        cout << files[i] << endl;
    }

    return 0;
}
