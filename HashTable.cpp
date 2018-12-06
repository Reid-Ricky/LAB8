//FILE NAME: HashTable.cpp
//
//HashTable program
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
#include "HashTable.h"

using namespace std;

HashTable::HashTable() {
    for (int i = 0; i < SIZE; i++) {
        table[i] = NULL;
    }
}

bool HashTable::isEmpty(int index) {
    /*
    if () {
        return true;
    }
    return false;
     */
    return true;
}



void HashTable::HashFunction(string key) {

}

void HashTable::insertData(int d) {

}

int HashTable::getData() {
    return 1;

}

int HashTable::getSize() {
    return SIZE;
}