/**********************************************
 * Last Name:   Abdulwaseem
 * First Name:  Bader
 * Student ID:  30023849
 * Course:      CPSC 457
 * Tutorial:    3
 * Assignment:  1
 * Question:    Q4
 *
 * File name: myWc.cpp
 *********************************************/

#include <unistd.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

int main (int argc, char * const argv[])
{
  // get the file name from command line
  string filename;
  if (argc != 2) {
    cerr << "Usage: readFile <input file> " << endl;
    return -1;
  }
  else {
    filename = argv[1];
  }

  // open the file for reading
  int fd = open(filename.c_str(), O_RDONLY);
  if(fd < 0) {
    cerr << "Could not open file " << filename << "\n";
    exit(-1);
  }

  // read file character by character and count lines
  int count = 0;
  while(1) {
    char c;
    if(read(fd, &c, 1) < 1) break;
    if(c == '\n') count ++;

  }

  // close file and report results
  close( fd);
  cout << count << " " << filename << "\n";
  return 0;
}
