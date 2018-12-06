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
int getNWordSequence(queue<string> nWordSequence, string file, int n);

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

        //cout << files[i] << '\n';
    }


    //****MAIN LOOP FOR FILLING HASHMAP****
    queue<string> nWordSequence; //store n word sequences
    int idx = 0; //index to keep track of what file
    while (idx < files.size()) {
        //clean file
        //-> while not end of file, infile << 6 word
        // maybe call getNwordsequence
        string word;
        ifstream current_file;
        string file = dir + "/" + files[idx];
        current_file.open(file.c_str());
        vector<string> file_words;
        while(current_file >> word) {
            for (int j =0;j<n;j++) {
                cleanString(word);
                file_words.push_back(word);
                current_file >> word;
            }
            for(int i = 0; i<file_words.size();i++){
                cout << file_words[i] << endl;
            }
        }
        //-cleanString (str.erase(str.begin + i))
        //findKey()
        // put each file on hash table
        //while (getNWordSequence(files[idx], n) == 1) {

        //}

        idx++;
    }

    //LOOP FOR MOVING HASHMAP TO 2D-ARRAY
    int* table[files.size()]; //stores collisions between files
    tableInit(table, files.size()); //initializes table

    //iterate through hashmap



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
    /*
    for(unsigned int i = 0;i < word.size();i++){
        if(word[i] <= 122 && word[i] >=97){
            word[i] = word[i] - 32;
        }
        else if(word[i] < 65 || word[i] > 90){
            word.erase(i,i);

    }
}
 */

}

int getNWordSequence(queue<string> nWordSequence, string file, int n) {
    return 0;
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
