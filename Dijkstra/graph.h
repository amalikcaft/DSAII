#ifndef _GRAPH_H
#define _GRAPH_H
#include <climits>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "hash.h"
#include "heap.h"
using namespace std;

class graph{

    private:
        //seperate class for graph vertices
        class vertex;
        //stores vertex and cost
        struct edge{
            public:
            int cost;
            vertex* nextV;
        };
        class vertex{
            public:
            string id;
            bool known;
            list<edge> adj;
            int distance;
            list<string> path;
        };
        hashTable* vertices;
        list<vertex*> visited;
        int capacity;


    public:
        graph();
        void load(ifstream &infile); //loads and reads graph
        void insert(string &v1, string &v2, int distance); //inserts into hashtable
        bool checkVertex(string &vertex); //checks if a vertex already exists
        void dijkstra(string &startVector); // implementation of dijkstra algorithm
        void printGraph(ofstream &outfile);// prints shortest paths of graph to out

};

#endif
