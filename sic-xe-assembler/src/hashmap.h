#ifndef _HASHMAP_H_
#define _HASHMAP_H_

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
//---------------------------//Notes on what Tyler Wants//----------------------------------------------------//
//   Tyler want the hash table as a class so we can use inheritance to make the semester project easier
//
//
//
//
//------------------------------------------------------------------------------------------------------------//
//---------------------------//Notes and tips//---------------------------------------------------------------//
//I am gonna need to create a hash node and hash map for the hash table
//
//
//
//  Hash Node will need
//  - Key
//  - Data value
//  - constructor and deconstructor(that excepts key value and data value as they will be stored in nodes)
//  - Pointer to the Nodes stored values (Aka Key and Data)
//
//
//  Hash Map will need
//  - Table Size (Which we won't really have)
//  - Hash Map Function to build an empty table
//  - Get function
//  - Insert Function (Where to put the new node)
//  - constructor and deconstructor
//
//
//------------------------------------------------------------------------------------------------------------//


//Hash node is a class doesn't really matter serves it purpose even if its  not a struct.
class hashNode{

    private:
        std::string key;
        int value;                     //will be working with strings as might make it easier hopefully.
        				// It doesn't. Changing to use integers instead. We want hexadecimal

    public:

	hashNode* next; // pointer to the next hashnode in the sublist.
			// i.e., the next node in this bucket

        hashNode(std::string key, int value){ //basic constructor taking in a key and string value.
            this->key = key;
            this->value = value;
	    this->next = NULL;
        }
        std::string getKey(){
            return key;
        }
        int getValue(){
            return value;
        }
};

//temporary until I figure a way to expand this piece of junk dynamically.

class hashMap{

    private:
        hashNode **table;
        int tableSize = 64;

    public:

        hashMap(){
            table = (hashNode**) malloc(sizeof(hashNode*) * tableSize);
	    //printf("%s: Allocated %db for table\n", __func__, sizeof(table));
            for(int i = 0; i < tableSize; i++){
                table[i] = NULL;
            }
        }

        int hash(std::string key);
        void setTableSize(int newSize);
        int search_Ele(std::string key);
        void insert(std::string key, int value);

        void print();

};


#endif //_HASHMAP_H
