//Ahmad Malik
//Fall 2022
//ECE 365
//Program 1
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "hash.h"
using namespace std;

int main(){
    string dictPath;
    ifstream dictionary;
    cout << "Enter dictionary file name: " <<endl;
    cin >> dictPath;
    clock_t start = clock(); //start dictionary load time
    dictionary.open(dictPath);
    if (dictionary.fail()){
        cerr << "ERROR: dictionary file FAILED to OPEN" << endl;
        _Exit(10);
    }
    //initialize hash table to load dictionary words
    hashTable *hash = new hashTable(500000);
    // convert all capital letters in dictionary file to lowercase
    string line;
    int i;
    while (getline(dictionary, line)){
        for (i = 0; i <= line.length(); i++){
            line[i] = tolower(line[i]);
        }
        hash->insert(line, nullptr);
    }
    dictionary.close();
    clock_t end = clock(); //end dictionary load time
    cout << "Dictionary Loading Time (seconds): " << ((double) (end-start)) / CLOCKS_PER_SEC << endl;
    //ask user for input and output files
    ifstream input;
    ofstream output;
    string inFile, outFile;
    cout << "Enter name of input file: " <<endl;
    cin >> inFile;
    input.open(inFile);
    if (input.fail()){
        cerr << "ERROR: input file FAILED to OPEN"<< endl;
        _Exit(10);
    }
    cout << "Enter name of output file: " << endl;
    cin >> outFile;
    output.open(outFile);
    if (output.fail()){
        cerr << "ERROR: output file FAILED to OPEN"<< endl;
        _Exit(10);
    }
    start = clock(); //start spellcheck processing
    //convert all letters to lowercase
    string word = "";
    unsigned long lineNumber = 1;
    bool ignoreWord = false;
    char c;
    int asciiVal;
    while (getline(input, line)) {
        for (i = 0; i <= line.length(); i++){ //check every word letter by letter
            c = tolower(line[i]);
            asciiVal = c;
            if ( (asciiVal >= 97) && (asciiVal <= 122) || (asciiVal == 39) || (asciiVal == 45)){ //ignore special characters
                word += c;
                if ((asciiVal >= 48) && (asciiVal <= 57)){//ignore words with digits
                    ignoreWord = true;
                }
            }
            else if ((ignoreWord == false) && (word.length() > 0)){
                if (word.length() > 20){ // max length of a word is 20 characters
                    output << "Long word at line " << lineNumber << ", starts: " << word.substr(0, 20) << endl;
                }
                else if (hash->contains(word) == false){    // report unknown words
                    output << "Unknown word at line " << lineNumber << ": " << word << endl;
                }
                word = "";
            }
        }
        lineNumber++;
    }
    end = clock();//end spellcheck processing
    cout << "SPELLCHECK COMPLETE\n" "Time to spellcheck file (seconds):  " << ((double) (end-start)) / CLOCKS_PER_SEC << endl;
    input.close();
    output.close();
    return 0;
}
