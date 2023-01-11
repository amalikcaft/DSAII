//Ahmad Malik
//ECE365
//Fall 2022
#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"
using namespace std;

//load infile and identify v1, v2, and path length distance
void graph::load(ifstream &infile){
    string v1, v2;
    int distance;
    while(infile >> v1 >> v2 >> distance){
        insert(v1, v2, distance); //load infile and identify v1, v2, and path length
    }
}

// If vertex doesn't exist, it is inserted
void graph::insert(string &v1,  string &v2, int distance){
    vertex *temp1;
    vertex *temp2;
    edge newEdge;
    //  create v2=1 if it hasn't been visited before, and record pointer to vertex
    if (!vertices -> contains(v1)){
        temp1 = new vertex;
        temp1 -> id = v1;
        temp1 -> known = false;
        temp1 -> distance = INT_MAX; // represents infinity
        visited.push_back(temp1);
        vertices -> insert(v1, temp1);
        capacity++;
    }
    else{
        temp1 = (vertex *)vertices -> getPointer(v1);
    }
    //create v2 if it hasn't been visited before,
    if (!vertices -> contains(v2)){
        temp2 = new vertex;
        temp2 -> id = v2;
        temp2 -> known = false;
        temp2 -> distance = INT_MAX;
        visited.push_back(temp2);
        vertices -> insert(v2, temp2);
        capacity++;
    }
    else{
        temp2 = (vertex *)vertices -> getPointer(v2);
    }
    newEdge.nextV = temp2;
    newEdge.cost = distance;
    temp1 -> adj.push_back(newEdge); //a new edge added to list, and will point to v2
}

void graph::dijkstra(string &startVector){
    //starting vertex pointer
    vertex *start = (vertex *)vertices -> getPointer(startVector);
    start -> distance = 0;
    start -> path.push_back(startVector);

    heap graphHeap(capacity);
    graphHeap.insert(startVector, start -> distance, start);
    for (list<vertex *>::iterator it = visited.begin(), end = visited.end();it != end; it++){
        if((*it) -> id != startVector){
            graphHeap.insert((*it) -> id, (*it) -> distance, *it);
        }
    }

    vertex *temp = nullptr;
    for (int i = 0; i < capacity; i++){
        graphHeap.deleteMin(nullptr, nullptr, &temp);
        temp -> known = true;
        for (list<edge>::iterator it = temp -> adj.begin(), end = temp -> adj.end(); (temp -> distance != INT_MAX)&& (it  != end) ; ++it){
            if ((it -> nextV -> distance > (it -> cost + temp -> distance))){
                if((temp -> distance != INT_MAX) && (!it -> nextV -> known)){
                    it -> nextV -> path.clear();
                    it -> nextV -> path.insert(it -> nextV -> path.begin(), temp -> path.begin(), temp -> path.end());
                    it -> nextV -> path.push_back(it -> nextV -> id);
                    it -> nextV -> distance = (it -> cost + temp -> distance);
                    graphHeap.setKey(it -> nextV -> id, (it -> cost + temp -> distance));
                }
            }
        }
    }
}

//iteratively find and print the shortest path to each vertices from the start vertex
void graph::printGraph(ofstream &outfile){
    list<vertex*> :: iterator it;
    list<string>::iterator i;
    //print each vertices shortest path to the output file
    for (it = visited.begin(); it != visited.end(); it++){
        outfile << (*it) -> id << ": ";
        if ((*it) -> distance == INT_MAX){
            outfile << "NO PATH" << endl; // If no path was found
        }
        else{
            outfile << (*it) -> distance << " [";
            for (i = (*it) -> path.begin(); i!= (*it) -> path.end(); i++){
                outfile << *i;
                if (next(i, 1)!= (*it) -> path.end()){
                    outfile << ", ";
                }
            }
            outfile << "]" << endl;
        }
    }
}

bool graph::checkVertex(string &vertex){
    return vertices -> contains(vertex);
}

graph::graph(){
   vertices = new hashTable(50000);
   capacity = 0;
}
