/*
Author: Bader Abdulwaseem
UCID: 30023849
Assignment 2
Question 2
*/


#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

using namespace std;

int main() {
    // Initializing the stack as a vector
    vector<string> stack;
    stack.push_back(".");

    while(stack.size()) {
        char dirPath[stack.size() + 1];
        // Copying string into char array then popping the stack
        string temp = *stack.end();
        strcpy(dirPath, temp.c_str());
        stack.pop_back();

        // Opening directory
        DIR *directory = opendir(dirPath);
        if (!directory) break;

        struct dirent *element = NULL;
        while(element = readdir(directory)) {
            string fullPath = string(dirPath) + "/" + string(element->d_name);
            if (element->d_type != DT_DIR) {
                cout << fullPath << endl;
            }
            else if (element->d_type == DT_DIR) {
                stack.push_back(fullPath);
            }
            closedir(directory);
        }

    }


    return 0;
}
