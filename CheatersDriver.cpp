//FILE NAME: CheatersDriver.cpp
//
//CheatersDriver Driver program
//Reid Lindemann & Ricky Guzman 12/06/2018
//EE 312

/* Student information for project:
 *
 * On my honor, Reid Lindemann and Ricky Guzman, this programming project is our own work
 * and I have not provided this code to any other student.
 *
 * Name: Reid Lindemann
 * email address: lindemannreid@yahoo.com
 * UTEID: rhl542
 * Section 5 digit ID: 16200
 *
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <queue>
#include <string>
#include <string.h>
#include <algorithm>
#include "HashTable.h"

using namespace std;

//uses directory to get the files
//INPUT: string of directory, vector of files
//OUTPUT: integer (0 or error message)
//**vector of files will be changed**
int getdir (string dir, vector<string> &files);

//rids the string of all punctuation and capitalizes it
//INPUT: string file name
//OUTPUT: n/a
void cleanString(string &word);

//concatenates vector of strings
//INPUT: vector of strings
//OUTPUT: string of key
string findKey(vector<string> v);

//outputs the files in order of the number of collisions
//INPUT: vector of strings, vector of integers
//OUTPUT: n/a
void outputFiles(vector<string> strings, vector<int> numbers);

int main(int argc, char *argv[]) {
    //LINUX COMMANDS
    //string dir(argv[1]);
    //int n = atoi(argv[2]);
    //int limit = atoi(argv[3]);

    //CLION COMMANDS
    string dir = "sm_doc_set";
    int n = 6;
    int threshold = 200;

    //OPEN DIRECTORY
    vector<string> files;
    getdir(dir, files);
    for (int i = 0; i < files.size(); i++) {
        if (files[i] == ".." || files[i] == ".") {
            files.erase(files.begin() + i);
            i--;
        }
    }

    //****MAIN LOOP FOR FILLING HASHMAP****
    HashTable hash;
    int idx = 0; //index to keep track of what file
    vector<string> n_words;
    while (idx < files.size()) {
        string word;

        //file stuff
        ifstream current_file;
        string file = dir + "/" + files[idx];
        current_file.open(file.c_str());

        n_words.clear();

        while(current_file >> word ) {

            //grab 6 words
            while (n_words.size() <= n) {
                cleanString(word);
                n_words.push_back(word);
                if (n_words.size() <= n) {
                    current_file >> word;
                }
            }

            //concatenate and call hashFunction()
            hash.hashFunction(findKey(n_words), idx);

            // delete first element in vector
            n_words.erase(n_words.begin());
        }

        idx++;
    }

    //****MAIN LOOP FOR MOVING HASHTABLE TO 2D-ARRAY****
    int table[files.size()][files.size()]; //stores collisions between files

    //initialize table
    for (int i = 0; i < files.size(); i++) {
        for (int j = 0; j < files.size(); j++) {
            if (j <= i) {
                table[i][j] = -1; //initialize inactive cells
            } else {
                table[i][j] = 0; //initialize active cells
            }
        }
    }

    int hashIter = 0; //used for going through hashtable
    int fileNum; //each file is numbered
    vector<int> pairs; //vector of all other collisions at hashtable location

    //iterate through hashtable
    while (hashIter < hash.getSize()) {
        //check if there is contents at hashtable location
        while (!(hash.indexIsEmpty(hashIter))) {

            //store and delete 1st node
            fileNum = hash.deleteFirstNode(hashIter);
            //check if valid
            if (fileNum != -1) {
                pairs.clear();
                //add each other file to 2D array
                pairs = hash.getDataOfIndex(hashIter);
                for (int i = 0; i < pairs.size(); i++) {
                    if (files[fileNum] != files[pairs[i]]) {
                        table[fileNum][pairs[i]] += 1; //increase count of collisions
                    }
                }
            }
        }

        hashIter++;
    }

    vector<string> output; //vector of string output
    vector<int> collisions; //vector of integer collisions
    for (int i = 0; i < files.size(); i++) {
        for (int j = 0; j < files.size(); j++) {
            if (table[i][j] > threshold) {
                collisions.push_back(table[i][j]);
                //output that will appear on screen
                string str = to_string(table[i][j]) + ": " + files[i] + ", " + files[j] + "\n";
                output.push_back(str);
            }
        }
    }

    //output to screen
    outputFiles(output, collisions);

    return 0;
}

//uses directory to get the files
//INPUT: string of directory, vector of files
//OUTPUT: integer (0 or error message)
//**vector of files will be changed**
int getdir (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

//rids the string of all punctuation and capitalizes it
//INPUT: string file name
//OUTPUT: n/a
void cleanString(string &word) {
    for (string::iterator iter = word.begin(); iter != word.end(); iter++) {
        //lower case -> capital
        if (*iter <= 122 && *iter >= 97) {
            *iter = *iter - 32;
        }
        //numbers
        if (*iter >= 48 && *iter <= 57) {
            //numbers do nothing!
        } else if (*iter < 65 || *iter > 90) {
            if (iter + 1  == word.end()){
                word.erase(iter);
                return;
            }
            word.erase(iter);
            iter--;
        }
    }
}

//concatenates vector of strings
//INPUT: vector of strings
//OUTPUT: string of key
string findKey(vector<string> v) {
    string key = "";
    for (int i = 0; i < v.size(); i++) {
        key = key + v[i]; //concatenate
    }
    return key;
}

//outputs the files in order of the number of collisions
//INPUT: vector of strings, vector of integers
//OUTPUT: n/a
void outputFiles(vector<string> strings, vector<int> numbers) {
    //bubble sort the vector of numbers (swap with vector of strings)
    for (int i = 0; i < numbers.size() - 1; i ++) {
        for (int j = 0; j < numbers.size() - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                swap(numbers[j], numbers[j + 1]);
                swap(strings[j], strings[j + 1]);
            }
        }
    }

    //output to screen
    for (int i = 0; i < strings.size(); i++) {
        cout << strings[i];
    }
}