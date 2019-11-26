//
// Created by Vincent Lee on 25/11/2019.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "variable.hpp"
#include "error.hpp"
#include "variableList.hpp"
#include "sharedLibrary.hpp"
#include "instructionList.hpp"
#include "assemblerFunctions.hpp"

using namespace std;

vector<vector<string>> processedInput;
variableList variableContainer;
instructionList instructionContainer;

void processInputFiles(string txtFile){
    ifstream reader(txtFile);

    if (!reader) {
        cout << "Error opening input file" << endl;
        return;
    }

    string line;
    while (getline(reader, line)){
        string chunk = "";
        vector<string> tempVector;
        for(char &l : line){
            if(l == ' ' && !chunk.empty()){
                tempVector.push_back(chunk);
                chunk = "";
            }else if(l == ';'){ // we break if we hit a comment
                break;
            }else if(l != ':' && l != ' '){
                chunk += l;
            }
        }
        if(!tempVector.empty()){
            processedInput.push_back(tempVector);
        }
    }
}

void processAssembly(){
    int firstInstruction = -1;
    int lastInstruction = -1;

    if(processedInput.empty()){
        throw NO_INSTRUCTION_TO_PROCESS;
    }

    int lineCount = 0;
    for(auto &line : processedInput){
        if(line.at(0) == "START"){
            firstInstruction = lineCount;
        }
        if(line.at(0) == "END"){
            lastInstruction = lineCount;
        }
        lineCount++;
    }

    if(firstInstruction == -1 || lastInstruction == -1){
        throw UNABLE_TO_FIND_START_OR_AND_END;
    }

    cout << firstInstruction << " | " << lastInstruction << endl;

    // We skip parsing the first line as it will always be
    // var 0

    //This starts first line that has a the START identifier
    vector<string> vectorTemp = processedInput.at(1);
    instructionContainer.addInstructions(vectorTemp.at(1), )

    for(int i = firstInstruction+1; i < lastInstruction; i++){

    }


}

void printVectorLine(){
    cout << "=======================" << endl;
    for(auto &i : processedInput){
        cout << endl;
        for(auto &o : i){
            cout << o << "|";
        }
    }
    cout << endl << "=======================" << endl;
}

int main(){
    processInputFiles("test.txt");
    processAssembly();
    printVectorLine();
}

