//FILE NAME: CheatersDriver.cpp
//
//CheatersDriver Driver program
//Reid Lindemann & Ricky Guzman 11/27/2018
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
#include "HashTable.h"

using namespace std;

//INPUT:
//OUTPUT:
int getdir (string dir, vector<string> &files);

//INPUT: string file name
//OUTPUT: number of words in file
void cleanString(string &word);

//INPUT:
//OUTPUT:
string findKey(vector<string> v);

//INPUT:
//OUTPUT:
void tableInit(int* table[], int max);

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
        ifstream current_file;
        string file = dir + "/" + files[idx];
        current_file.open(file.c_str());
        n_words.clear();
        while(current_file >> word) {
            //grab 6 words
            while (n_words.size() <= n) {
                cleanString(word);
                n_words.push_back(word);
            }
            cout << findKey(n_words) << endl;
            //concatenate and call hashFunction()
            //hash.hashFunction(findKey(n_words), idx);

            // delete first element in queue
            n_words.erase(n_words.begin());
        }
        idx++;
    }

    //LOOP FOR MOVING HASHMAP TO 2D-ARRAY
    int* table[files.size()]; //stores collisions between files
    tableInit(table, files.size()); //initializes table

    //iterate through hashmap
    /*
    int i = 0;
    while (i < hash.getSize()) {
        while (hash.isEmpty(i) == false) {

        }
        i++;
    }
    */

    //determine what files were cheating
    for (int i = 0; i < files.size(); i++) {
        for (int j = 0; j < files.size(); j++) {
            if (table[i][j] > threshold) {
                //print to screen
            }
        }
    }

    return 0;
}

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

void cleanString(string &word) {
    for (string::iterator iter = word.begin(); iter != word.end(); iter++) {
        if (*iter <= 122 && *iter >= 97) {
            *iter = *iter - 32;
        }
        if(*iter >= 48 && *iter <= 57){

        }else if (*iter < 65 || *iter > 90) {
            if(iter +1  == word.end()){
                word.erase(iter);
                return;
            }
            word.erase(iter);
        }
    }
}

string findKey(vector<string> v) {
    string key = "";
    for (int i = 0; i < v.size(); i++) {
        key = key + v[i];
    }
    return key;
}

void tableInit(int* table[], int max) {
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < max; j++) {
            if (j <= i) {
                table[i][j] = -1; //initialize inactive cells
            } else {
                table[i][j] = 0; //initialize active cells
            }
        }
    }
}
