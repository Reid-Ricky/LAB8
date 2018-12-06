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


bool HashTable::indexIsEmpty(int index) {
    if (table[index] == NULL) {
        return true;
    }
    return false;
}


void HashTable::hashFunction(const string &key, int data) {
    int unsigned long idx = 0;
    int unsigned long mult = 1;
    for (int i = 0; i < key.size(); i+2) {
        idx = idx + (((key[i]) * mult) % SIZE);
        mult = mult*9;
    }
    HashNode* ptr = new HashNode;
    ptr->data = data;
    ptr->next = table[idx];
    table[idx] = ptr;
}

//return data after delete
//-1 is empty, data is positive number
int HashTable::deleteFirstNode(int index) {
    int num;
    if (table[index] == NULL) {
        return -1;
    } else {
        HashNode* buff = table[index];
        num = table[index]->data;
        table[index] = table[index]->next;
        delete buff;
    }
    return num;
}


vector<int> HashTable::getDataOfIndex(int index) {
    vector<int> v;
    HashNode* ptr = table[index];
    while (ptr != NULL) {
        v.push_back(ptr->data);
        ptr = ptr->next;
    }
    return v;
}


int HashTable::getSize() {
    return SIZE;
}


HashTable::~HashTable() {
    for (int i = 0; i < SIZE; i++) {
        while (deleteFirstNode(i) != -1) {}
    }
}