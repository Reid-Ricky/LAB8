//FILE NAME: HashTable.cpp
//
//HashTable program
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
#include "HashTable.h"

using namespace std;

//Default Constructor
HashTable::HashTable() {
    for (int i = 0; i < SIZE; i++) {
        table[i] = NULL;
    }
}

//INPUT: integer of index
//OUTPUT: boolean of emptiness
//Precondition: index is valid
bool HashTable::indexIsEmpty(int index) {
    if (table[index] == NULL) {
        return true;
    }
    return false;
}

//INPUT: string concatenation, integer of data
//OUTPUT: n/a
void HashTable::hashFunction(const string &key, int data) {
    int unsigned long idx = 0;
    int unsigned long mult = 1;
    const int primeMultiplier = 11;
    //skips every other element to determine index
    for (int i = 0; i < key.size(); i+=2) {
        idx = idx + (((key[i]) * mult));
        mult = mult*primeMultiplier;
    }
    idx = idx % SIZE;
    HashNode* ptr = new HashNode; //dynamic memory allocation
    ptr->data = data;
    ptr->next = table[idx];
    table[idx] = ptr;
}

//INPUT: intger of index
//OUTPUT: integer of deleted data (-1 if empty, positive int is data)
//Precondition: index is valid
int HashTable::deleteFirstNode(int index) {
    int num;
    if (table[index] == NULL) {
        return -1;
    } else {
        HashNode* buff = table[index];
        num = table[index]->data;
        table[index] = table[index]->next;
        delete buff; //delete dynamic memory
    }
    return num;
}

//INPUT: integer of index
//OUTPUT: vector of data of each node in the list of array at index
//Precondition: index is valid
vector<int> HashTable::getDataOfIndex(int index) {
    vector<int> v;
    HashNode* ptr = table[index];
    while (ptr != NULL) {
        v.push_back(ptr->data);
        ptr = ptr->next;
    }
    return v;
}

//INPUT: n/a
//OUTPUT: integer of size
int HashTable::getSize() {
    return SIZE;
}

//Destructor
HashTable::~HashTable() {
    for (int i = 0; i < SIZE; i++) {
        while (deleteFirstNode(i) != -1) {}
    }
}