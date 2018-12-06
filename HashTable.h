//FILE NAME: HashTable.h
//
//HashTable Header program
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

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <vector>

using namespace std;

//HashTable class declaration
class HashTable {
      
  private:
    static const int SIZE = 100001; //MUST BE PRIME

    struct HashNode {
        int data;
        HashNode* next;
    };

    HashNode* table[SIZE];
 
  public:

    //Default constructor
    HashTable();

    //checks to see if array at index is empty
    bool indexIsEmpty(int index);

    //determines index of hash table from key and inserts
    void hashFunction(const string &key, int data);

    //deletes the first node of array at index
    int deleteFirstNode(int index);

    //returns the data of each node in the list of array at index
    vector<int> getDataOfIndex(int index);

    //returns size of array
    int getSize();

    //Destructor
    ~HashTable();
 };



#endif
