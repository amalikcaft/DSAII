//Ahmad Malik
//ECE365
//Fall 2022
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "hash.h"
using namespace std;

// Constructor to initialize hashTable capacity and size
hashTable::hashTable(int size) : capacity(getPrime(size)), data(capacity), filled(0){}
// Insert new value to hash table


int hashTable::insert(const std::string &key, void *pv){
	// Rehash when more than half the hashTable capacity is filled
	int check;
    if ((filled) >= ((capacity)/2)) check = rehash();
    if (check == 2){
            return 2;
    }
	int index = hash(key);
	// Search for key in hashTable and first available spot
	if ((data[index].isDeleted == false) && (data[index].key == key)){
		return 1; //returns 1 if key is already in hash table
	}
    while ((data[index].key != key) && (data[index].isOccupied || data[index].isDeleted)){
		index++;
        if (index == capacity)
            index = 0;
	}
	// Insert new key at data[index]
	data[index].key = key;
	data[index].pv = pv;
	data[index].isOccupied = true;
	data[index].isDeleted = false;
	filled++;
	return 0; // returns 0 on successful insertion,
}

//return true if hash table contains key, otherwise false
bool hashTable::contains(const std::string &key){
	if(findPos(key) != -1){
		return true;
	}
	else{
		return false;
	}
}

//delete item from hash table
bool hashTable::remove(const std::string &key){
	int index = findPos(key);
	if (index == -1){
		return false;
	}
	else{
		data[index].isOccupied = false;
		data[index].isDeleted = true;
		return true;
	}
}

// Hash function from https://stackoverflow.com/questions/7700400/whats-a-good-hash-function-for-english-words
int hashTable::hash(const std::string &key){
	unsigned long hash = 5381;
    int c;
	int i = 0;
    while (c = key[i++])
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % capacity;
}

//returns index given a key
int hashTable::findPos(const std::string &key){
	int index = hash(key);
	while (data[index].isOccupied || data[index].isDeleted){
        if(data[index].key == key && !data[index].isDeleted){
                return index;
        }
        else{
                index++;
                if (index == capacity)index = 0;
        }
    }
	return -1; //if key not found
}

bool hashTable::rehash(){
    vector<hashItem> temp = data;
    try{
		data.resize(getPrime(capacity));
	}
    catch (std::bad_alloc){
        cout << "ERROR: Unable to Rehash" << endl;
        return false;
	}
    capacity = getPrime(capacity);
    filled = 0;
    for (int i = 0; i < data.size(); i++){
        data[i].key = "";
	    data[i].pv = nullptr;
        data[i].isOccupied = false;
        data[i].isDeleted = false;
		}
    for (int i = 0; i < temp.size(); i++){
        hashItem item = temp[i];
        if ((item.isOccupied == true) && (item.isDeleted == false)){
            insert(item.key, item.pv);
		}
    }
    return true;
}

// return the first prime number larger than twice the size: https://planetmath.org/goodhashtableprimes
unsigned int hashTable::getPrime(int size){
	static unsigned int primeNumbers[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
										  786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917, 25165843,
										  50331653, 100663319, 201326611, 402653189, 805306457, 1610612741};
	for (int i = 0 ; i <= sizeof(primeNumbers)/sizeof(int); i++) {
		if ( primeNumbers[i] >= (2*size)){
			return primeNumbers[i];
		}
	}
	return primeNumbers[29];
}


void* hashTable::getPointer(const std::string &key, bool *b){
    int index= findPos(key);
    if(index>= 0){
        if(b != nullptr){
			*b = true;
        }
        return data[index].pv;
    }
    else{
        if(b != nullptr){
            *b = false;
        }
        return nullptr;
    }
}

int hashTable::setPointer(const std::string &key, void *pv){
    int index= findPos(key);
    if(index!= -1){
        data[index].pv = pv;
        return 0;
    }
    else{
        return 1;
    }
}
