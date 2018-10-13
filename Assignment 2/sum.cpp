#include <iostream>
#include <vector>
#include <fstream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

struct dataOfThread {
	int threadID, partialSum;
	vector<int> numbers;
};

// Creating summation function for the threads
void* start_func(void *arg) {
	dataOfThread data = *(dataOfThread*) arg;
	int totalSum = 0;
	for (int i = 0; i < data.numbers.size(); i++) {
		totalSum += data.numbers[i];
	}
	data.partialSum = totalSum;
}


int main(int argc, char *argv[]) {

	// Checks to see if the program is being run with the correct inputs
	if (argc != 3) {
		cout << "This program takes two arguments in this format: 'input' 'thread count'" << endl;
		return 1;
	}

	char *fileName = argv[1];
	// Converting the string into integer
	int numberOfThreads = stoi(argv[2]);

	vector<int> numbersFromInput;
	ifstream inputFile;
	inputFile.open(fileName);
	if (!inputFile.is_open()) {
		cout << "Failed to open file." << endl;
		return 1;
	}

	// Reading from the file and storing all the numbers in a vector
	string numStr;
	while (getline(inputFile, numStr)) {
		numbersFromInput.push_back(stoi(numStr));
	}
	inputFile.close();

	// Declaring threads
	pthread_t sumThreads[numberOfThreads];
	dataOfThread data[numberOfThreads];

	// Splitting the data for each thread
	int firstHalf = numbersFromInput.size() % numberOfThreads;
	int firstHalfSize = (numbersFromInput.size() / numberOfThreads) + 1;
	int secondHalf = numberOfThreads - firstHalf;
	int secondHalfSize = numbersFromInput.size() / numberOfThreads;

	for (int i = 0; i < firstHalf; i++) {
		int offset = i * firstHalfSize;
		for (int j = i * firstHalfSize; j < offset + firstHalfSize; j++) {
			data[i].numbers[j] = numbersFromInput[j];
		}
	}

	for (int i = secondHalf; i < numberOfThreads; i++) {
		int offset = i * secondHalfSize;
		for (int j = i * secondHalfSize; j < offset + secondHalfSize; j++) {
			data[i].numbers[j] = numbersFromInput[j];
		}
	}

	// Creating threads
	for (int i = 0; i < numberOfThreads; i++) {
		data[i].threadID = i;
		pthread_create(&sumThreads[i], NULL, start_func, &data[i]);
	}

	// Joining threads
	for (int i = 0; i < numberOfThreads; i++) {
		pthread_join(sumThreads[i], NULL);
	}

	// Printing and calculating total sum
	int totalSum = 0;
	for (int i = 0; i < numberOfThreads; i++) {
		cout << "Thread ID " << data[i].threadID << ": " << data[i].partialSum << endl;
		totalSum += data[i].partialSum;
	}

	cout << "Total sum: " << totalSum << endl;

	return 0;
}
