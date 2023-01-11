//Ahmad Malik
//ECE365
//Fall 2022
#include "heap.h"
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

//constructor to initialize heap
heap::heap(int capacity){
    data.resize(capacity+1);
    IDmapping = new hashTable(capacity * 2);
    this->capacity = capacity;
    filled = 0;
}

int heap::insert(const std::string &id, int key, void *pv){
    if (filled == capacity){
        return 1;
    }
    //insert data into binary tree if id doesn't already exist
    if (!(IDmapping->contains(id))){
        filled ++;
        data[filled].id = id;
        data[filled].key = key;
        data[filled].pData = pv;
        IDmapping->insert(id, &data[filled]);
        percolateUp(filled);
        return 0;
    }
    else{
        return 2;
    }
}

int heap::setKey(const std::string &id, int key){

    if (!(IDmapping->contains(id))){ //checking if id already exists
        return 1;
    }
    Node *Nptr = static_cast<Node *>(IDmapping->getPointer(id));  // find node using hashtable
    int oldkey = Nptr->key;
    Nptr->key = key;
    int npos = getpos(Nptr);

    if (key > oldkey){
        percolateDown(npos);
    }
    else if (key < oldkey){
        percolateUp(npos);
    }
    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData){
    if (!(IDmapping->contains(id))){ // check if id already exists
        return 1;
    }
    Node *Nptr = static_cast<Node *>(IDmapping->getPointer(id)); // find node using hashtable
    if (ppData != nullptr){
        *(static_cast<void **>(ppData)) = Nptr->pData;
    }
    if (pKey != nullptr){
        *pKey = Nptr->key;
    }
    setKey(id, INT_MIN);
    deleteMin();
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData){
    if (filled == 0){ // Check if heap is empty
        return 1;
    }
    else{
        Node min = data[1];
        IDmapping->remove(min.id);
        if (pKey != nullptr){
            *pKey = min.key;
        }
        if (pId != nullptr){
            *pId = min.id;
        }
        if (ppData != nullptr){
            *(static_cast<void **>(ppData)) = data[1].pData;
        }
        data[1] = data[filled--];
        percolateDown(1); //percolate down once top is removed
        return 0;
    }
}

int heap::getpos(Node *ptr){
    return (ptr - &data[0]);
}

void heap::percolateUp(int pos){ //move a node up through the binary heap
    data[0] = data[pos]; // storing new node temporarily
    Node inserted = data[pos];
    for (; pos > 1 && inserted.key < data[pos / 2].key; pos /= 2){ // percolate up through the heap
        data[pos] = data[pos / 2];
        IDmapping->setPointer(data[pos].id, &data[pos]);
    }
    data[pos] = data[0]; // inserting new node
    IDmapping->setPointer(data[pos].id, &data[pos]);
}

void heap::percolateDown(int pos){ //move a node down through the binary heap
    int child;
    Node removed = data[pos]; //store node temporarily
    for (; pos * 2 <= filled; pos = child){
        child = pos * 2;
        if (child != filled && data[child + 1].key < data[child].key){
            child++;
        }
        if (data[child].key < removed.key){ // check if child is smaller than parent
            data[pos] = data[child];
            IDmapping->setPointer(data[pos].id, &data[pos]);
        }
        else{
            break; //break if node satisfies binary heap condition
        }
    }
    data[pos] = removed;
    IDmapping->setPointer(data[pos].id, &data[pos]);
}
