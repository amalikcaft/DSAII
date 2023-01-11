//Ahmad Malik
//ECE365
//Fall 2022
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int matrix[1001][1001];

string isMerge(string A, string B, string C){

    int lenA = A.length();
    int lenB = B.length();
    int lenC = C.length();
    if (lenA + lenB != lenC){
        return "*** NOT A MERGE ***";
    }
    else {
       matrix[0][0] = 1;
       //fill matrix with 2 or 3 if A or B are interweaved
        for (int j = 0; j <= lenB; j++){
            for (int i = 0; i <= lenA; i++){
                if (matrix[i][j]){
                    if (A[i] == C[i + j] && !matrix[i + 1][j]){
                        matrix[i + 1][j] = 2;
                    }
                    if (B[j] == C[i + j] && !matrix[i][j + 1]){
                        matrix[i][j + 1] = 3;
                    }
                }
            }
        }
        //Change C so that A merged is Uppercase
        if (matrix[lenA][lenB]){
            while (lenA > 0 && lenB >= 0){
                if (matrix[lenA][lenB] == 2){
                    C[lenA + lenB - 1] = toupper(C[lenA + lenB - 1]);
                    lenA--;
                }
                else{
                    lenB--;
                }
            }
            return C;
        }
        else{
            return "*** NOT A MERGE ***";
        }
    }
}

int main(){
    string infile, outfile;
    cout << "Enter name of input file: ";
	cin >> infile;
    cout << "Enter name of output file: ";
    cin >> outfile;

    ifstream input;
    ofstream output;
    input.open(infile);
    output.open(outfile);

    string A,B,C;
    while(input >> A >> B >> C){
        //initialize matrix to 0
        for(int i = 0; i < A.size() + 1; i++){
            for (int j = 0; j < B.size() + 1; j++){
                matrix[i][j] = 0;
            }
        }
        output << isMerge(A,B,C) << '\n';
    }
    input.close();
    return 0;
}
