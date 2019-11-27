//
// Created by Vincent Lee on 25/11/2019.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "variable.hpp"
#include "error.hpp"
#include "variableList.hpp"
#include "sharedLibrary.hpp"
#include "instructionList.hpp"

using namespace std;

vector<vector<string>> processedInput;
variableList variableContainer;
instructionList instructionContainer;

/**
 * Turns mnemonic into function numbers
 * @param mnemonic
 * @return the function number
 */
int mnemonicToInt(string mnemonic){
    if(mnemonic == "JMP"){
        return 0;
    }else if(mnemonic == "JRP"){
        return 1;
    }else if(mnemonic == "LDN"){
        return 2;
    }else if(mnemonic == "STO"){
        return 3;
    }else if(mnemonic == "SUB"){
        return 4;
    }else if(mnemonic == "CMP"){
        return 6;
    }else if(mnemonic == "STP"){
        return 7;
    }else{
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
}

void processInputFiles(string txtFile){
    ifstream reader(txtFile);

    if (!reader) {
        cout << "Error opening input file" << endl;
        throw FILE_IO_ERROR;
    }

    string line;
    while (getline(reader, line)){
        string chunk = ""; //Used to temp hold chars as we process them
        vector<string> tempVector; // creates a temp vector for holding strings
        for(char &l : line){ //
            if(l == ' ' && !chunk.empty()){
                tempVector.push_back(chunk);
                chunk = "";
            }else if(l == ';'){ // we break if we hit a comment as the semi-collon and anything after is a comment
                break;
            }else if(l != ':' && l != ' '){
                chunk += l;
            }
        }
        // If the tempory vector for the line we just processed isn't empty we push it to the vector
        if(!tempVector.empty()){
            processedInput.push_back(tempVector);
        }
    }
    reader.close();
}

void processAssembly(){

    if(processedInput.empty()){
        throw INPUT_PROCESS_FAILED;
    }

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

    // We skip parsing the first line as it will always be
    // var 0

    //This starts first line that has a the START identifier
    vector<string> vectorTemp = processedInput.at(firstInstruction);
    instructionContainer.addInstructions(vectorTemp.at(2), mnemonicToInt(vectorTemp.at(1)));

    //Places all the instructions between the first and last instruction in the assembly file
    for(int i = firstInstruction+1; i < lastInstruction; i++){
        vectorTemp = processedInput.at(i);
        instructionContainer.addInstructions(vectorTemp.at(1), mnemonicToInt(vectorTemp.at(0)));
    }

    // This parses the last instruction in the assembly file
    vectorTemp = processedInput.at(lastInstruction);
    instructionContainer.addInstructions(mnemonicToInt(vectorTemp.at(1)));

    // This assignees the memory locations of the instructions.
    instructionContainer.bulkSetMemoryLocation(1); // this is set to 1 as the MB starts its IC from 1 instead of 0

    // For item after the last instruction that's a var
    for(int i = lastInstruction+1; i < (int)processedInput.size(); i++){
        vectorTemp = processedInput.at(i);
        if(vectorTemp.at(1) == "VAR"){
            variableContainer.addVariable(vectorTemp.at(0), stoi(vectorTemp.at(2)));
        }
    }

    // This assigns the memory locations of the variables, from the last instructions
    variableContainer.bulkSetMemoryLocation(instructionContainer.getInstructionListSize()+1);

}

void outputMachineCode(string writeFile){
    if(variableContainer.sizeOfVariableList() == 0 || instructionContainer.getInstructionListSize() ==0){
        throw INPUT_PROCESS_FAILED;
    }
    if(writeFile.empty()){
        throw INVALID_INPUT;
    }

    ofstream outputFile(writeFile);
    if(!outputFile.is_open()){
        cout << "Error opening input file" << endl;
        throw FILE_IO_ERROR;
    }

    outputFile << "00000000000000000000000000000000" << endl;

    // for each instruction in the Instruction Container
    for(int i = 0; i < (int)instructionContainer.getInstructionListSize(); i++){
        instruction tempInstruct = instructionContainer.getItemInInstructionList(i);
        string stringBuilder = "";
        int lineNo = 0;
        try {
            lineNo = variableContainer.getMemoryLocation(tempInstruct.getVariable());
        }catch(...){
            //This try catch is to catch any time we looks for a variable that doesn't exist,
            //like when the string is blank, e.g. STP command
        }
        stringBuilder += reverseString(memoryLocationToBinary(lineNo));
        stringBuilder += "00000000";
        stringBuilder += reverseString(instructionToBinary(tempInstruct.getFunctionNumber()));
        stringBuilder += "0000000000000000";
        outputFile << stringBuilder << endl;
    }

    // for each variable in variable container
    for(int i = 0; i < variableContainer.sizeOfVariableList(); i++){
        outputFile << reverseString(toBinary(variableContainer.getVariable(i).getVariableValue())) << endl;
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
    try {
        outputMachineCode("output.txt");
    }catch(int& e){
        cout << "exception: " << e << endl;
    }

}

