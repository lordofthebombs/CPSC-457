/// counts number of primes from standard input
///
/// compile with:
///   $ gcc findPrimes.c -O2 -o count -lm
///
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <pthread.h>
#include <vector>

struct threadData {
    int threadCount;
    int partialCount;
    int id;
    std::vector<int64_t> numbers;
};

/// primality test, if n is prime, return 1, else return 0
int isPrime(int64_t n)
{
     if( n <= 1) return 0; // small numbers are not primes
     if( n <= 3) return 1; // 2 and 3 are prime
     if( n % 2 == 0 || n % 3 == 0) return 0; // multiples of 2 and 3 are not primes
     int64_t i = 5;
     int64_t max = sqrt(n);
     while( i <= max) {
         if (n % i == 0 || n % (i+2) == 0) return 0;
         i += 6;
     }
     return 1;
}


// Partially counts all the primes in the vector of threadData
void * countPrimes (void * arg) {
    threadData *data = (threadData*) arg;
    int count = 0;


    for (int i = data->id; i < data->numbers.size(); i += data->threadCount) {
        if (isPrime(data->numbers[i])) {
            count++;
        }
    }

    data->partialCount = count;

    return NULL;
}

int main(int argc, char ** argv)
{
    /// parse command line arguments
    int nThreads = 1;
    if (argc != 1 && argc != 2) {
        printf("Usage: countPrimes [nThreads]\n");
        exit(-1);
    }
    if (argc == 2) nThreads = atoi(argv[1]);

    /// handle invalid arguments
    if (nThreads < 1 || nThreads > 256) {
        printf("Bad arguments. 1 <= nThreads <= 256!\n");
    }

    // Declaring threads
    pthread_t thread[nThreads];
    threadData data[nThreads];

    /// count the prime
    if (nThreads == 1) {
        printf("Counting primes using %d thread.\n", nThreads);
    }
    else {
        printf("Counting primes using %d threads.\n", nThreads);
    }


    int64_t count = 0;
    std::vector<int64_t> numbers;


    if (nThreads != 1) {
        while (1) {
            int64_t num;
            if (1 != scanf("%ld", &num)) break;
            numbers.push_back(num);
        }

        // Creating threads
        for (int i = 0; i < nThreads; i++) {
            data[i].id = i;
            data[i].numbers = numbers;
            data[i].threadCount = nThreads;
            pthread_create(&thread[i], NULL, countPrimes, &data[i]);
        }


        // Joining threads
        for (int i = 0; i < nThreads; i++) {
            pthread_join(thread[i], NULL);
        }

        // Summing up partial counts
        for (int i = 0; i < nThreads; i++) {
            count += data[i].partialCount;
        }
    }

    else {
        while (1) {
            int64_t num;
            if (1 != scanf("%ld", &num)) break;
            if (isPrime(num)) count ++;
        }
    }
    /// report results
    if (count == 1) {
        printf("Found %ld prime.\n", count);
    }

    else {
        printf("Found %ld primes.\n", count);
    }

    return 0;
}
