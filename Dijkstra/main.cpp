//Ahmad Malik
//ECE365
//Fall 2022
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include "graph.h"
using namespace std;

int main(){
    
    string infile, outfile, startVertex;
    ifstream input;
    ofstream output;
    graph g;

    //load graph file
    cout << "\nEnter name of graph file: " ;
    cin >> infile;
    input.open(infile, ifstream::in);
    g.load(input);
    input.close();

    //enter starting vertex name
    do{
		cout << "Enter name of starting vertex: ";
		cin >> startVertex;
	}while (g.checkVertex(startVertex) == false);

    //calculate time to perform dijkstra's algorithm
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now(); //START
    g.dijkstra(startVertex);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now(); //END
	chrono::duration<double> timeDiff = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "Total processing time (in seconds): " << fixed << timeDiff.count() << endl;

    //enter output file name
    cout << "Enter name of output file: ";
    cin >> outfile;
    output.open(outfile, ofstream::out | ofstream::trunc);
    g.printGraph(output);
    output.close();
    return 0;
}
