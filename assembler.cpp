//
// Created by Vincent Lee on 25/11/2019.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include "error.hpp"
#include "variableList.hpp"
#include "sharedLibrary.hpp"
#include "instructionList.hpp"

using namespace std;

vector<vector<string>> processedInput; // Holds the input file after it's cleaned up
variableList variableContainer; // Holds all the variables used in the assembly file
instructionList instructionContainer; // Holds all the instructions states in the assembly file
const string arrayMnemonics[7] = {"JMP", "JRP", "LDN", "STO", "SUB", "CMP", "STP"};
const int arrayFunctionNo[7] =  {0 ,1, 2, 3, 4, 6, 7};

vector<string> mnemonics;
vector<int> functionNumbers;

/**
 * sets ip program vectors
 */
void setup(){
    //places the mnemonic and function Numbers from their arrays into their vectors
    for(auto &item : arrayMnemonics){
        mnemonics.push_back(item);
    }
    for(auto &item : arrayFunctionNo){
        functionNumbers.push_back(item);
    }
}

/**
 * Allows for setting custom mnemonics and function numbers via a config txt file
 * @param configFile the config txt file to go off of.
 */
void configMnemonicsAndFunctionNumbers(string configFile){
    ifstream reader(configFile);

    if (!reader) {
        cout << "Error opening config file" << endl;
        throw FILE_IO_ERROR;
    }

    string line;
    while (getline(reader, line)){    // read file line by line
        string option;
        for(auto &c : line){
            if(c == ':'){
                break;
            }else{
                option+= c;
            }
        }

        if(option == "mnemonics"){ //if we find the keyword
            mnemonics.clear();
            string newMnemonics = "";
            bool startOfInput = false;
            //This gets all the chars between the backets in the config file
            for(auto &c : line){
                if(c == '['){
                    startOfInput = true;
                }else if(startOfInput && c != ']'){
                    newMnemonics += c;
                }else if(c == ']'){
                    break;
                }
            }
            stringstream mnemonicsStream (newMnemonics);
            string temp;
            while(getline(mnemonicsStream, temp, ' ')){
                mnemonics.push_back(temp);
            }
        }else if(option == "functionNumbers"){
            functionNumbers.clear();
            string newFunctionNo = "";
            bool startOfInput = false;
            //This gets all the chars between the backets in the config file
            for(auto &c : line){
                if(c == '['){
                    startOfInput = true;
                }else if(startOfInput && c != ']'){
                    newFunctionNo += c;
                }else if(c == ']'){
                    break;
                }
            }
            stringstream functionNoStream (newFunctionNo);
            string temp;
            while(getline(functionNoStream, temp, ' ')){
                functionNumbers.push_back(stoi(temp));
            }
        }
    }
    // Checks if the size of both vectos are the same
    if(mnemonics.size() != functionNumbers.size()){
        throw MISS_MATCHING_VECTOR;
    }
}

/**
 * Prints out config and the mnemonics and function Number combos
 */
void printConfig(){
    cout << "================================================" << endl;
    cout << "                    The config" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "numberOfInstructionsConfig: " << numberOfInstructionsConfig << endl;
    cout << "numberOfMemoryLocationsConfig: " << numberOfMemoryLocationsConfig << endl;
    cout << "bitsNotUserAfterLineNo: " << bitsNotUserAfterLineNo << endl;
    cout << "bitsNotUsedAfterFunctionNumber: " << bitsNotUsedAfterFunctionNumber << endl;
    cout << "bitsUsedForLineNo: " << bitsUsedForLineNo << endl;
    cout << "bitsUsedForFunctionNo: " << bitsUsedForFunctionNo << endl;
    cout << "================================================" << endl;
    cout << "          Mnemonics & Function Numbers" << endl;
    cout << "-------------------------------------------------" << endl;
    for(int loc = 0; loc < (int)mnemonics.size(); loc++){
        cout << mnemonics.at(loc) << " | " << functionNumbers.at(loc) << endl;
    }
    cout << "================================================" << endl;
}

/**
 * Turns mnemonic into function numbers
 * @param mnemonic
 * @return the function number
 */
int mnemonicToInt(const string& mnemonic){

    // for each item in the mnemonics vector
    for(int loc = 0; loc < (int)mnemonics.size(); loc++){
        // if the mnemonic we're looking for is in the mnemonics vector
        if(mnemonics.at(loc) == mnemonic){
            // return the corresponding function number
            return functionNumbers.at(loc);
        }
    }

    // If we're gone through the whole loop with out find the mnemonics
    // it means it doesn't exist and we throw an error
    throw INSTRUCTION_DOES_NOT_EXIST;
}

/**
 * Takes the input assembly txt file and places the cleaned contents into the processedInput vector
 * @param txtFile the file to read into
 */
void processInputFiles(const string& txtFile){

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

/**
 * Processes the assembly file in the processedInput Vector into variable and instruction containers
 */
void processAssembly(){
    vector<string> vectorTemp; // This variable is a temp holding locations for the line we're processing at the time.

    // Check if we have data to process.
    if(processedInput.empty()){
        throw INPUT_PROCESS_FAILED;
    }

    int firstInstruction = -1;
    int lastInstruction = -1;

    if(processedInput.empty()){
        throw NO_INSTRUCTION_TO_PROCESS;
    }

    // this looks through the input and find where the END and START
    // of the instructions are.
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

    // If we can't find START or END we throw an error
    if(firstInstruction == -1 || lastInstruction == -1){
        throw UNABLE_TO_FIND_START_OR_AND_END;
    }

    for(int i = 0; i < firstInstruction; i++){
        vectorTemp = processedInput.at(i);
        if(vectorTemp.at(1) == "VAR"){
            variableContainer.addVariable(vectorTemp.at(0), stoi(vectorTemp.at(2)));
        }
    }

    //This starts first line that has a the START identifier
    vectorTemp = processedInput.at(firstInstruction);
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
    variableContainer.bulkSetMemoryLocation((int)instructionContainer.getInstructionListSize()+1);

}

/**
 * Re-asembles the Variable and Instruction containers into machine code
 * @param writeFile the file to output the machine code to.
 */
void outputMachineCode(const string& writeFile){
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

    // if the variables and instruction to output to machine code are
    // less the the number of memory locations we start the first line as a 0s
    if((int)variableContainer.sizeOfVariableList() + (int)instructionContainer.getInstructionListSize() < numberOfMemoryLocationsConfig-1){
        outputFile << "00000000000000000000000000000000" << endl;
    }


    // for each instruction in the Instruction Container
    for(int i = 0; i < (int)instructionContainer.getInstructionListSize(); i++){
        instruction tempInstruct = instructionContainer.getItemInInstructionList(i);
        string stringBuilder = ""; // holds string to place into machine code output
        int lineNo = 0;
        try {
            lineNo = variableContainer.getMemoryLocation(tempInstruct.getVariable());
        }catch(...){
            //This try catch is to catch any time we looks for a variable that doesn't exist,
            //like when the string is blank, e.g. STP command
            if(tempInstruct.getFunctionNumber() != 7){ // we check if it's the stp function
                throw VARIABLE_USED_BUT_NOT_DEFINED;
            }
        }
        // get the line number and work out the binary version
        string binaryLineNo = intToBinary(lineNo);
        if(binaryLineNo.length() > bitsUsedForLineNo){
            throw LINE_NUMBER_TO_LARGE_FOR_BITS_DEFINED;
        }
        stringBuilder += reverseString(binaryLineNo); // places line number into the line output string
        // This for loop places the spacing between the line number and function number
        int spacingNeeded = (bitsUsedForLineNo + bitsNotUserAfterLineNo) - (int)binaryLineNo.length();
        for(int x = 0; x < spacingNeeded; x++){
            stringBuilder += '0';
        }

        // get the function number and output it into the line output string
        string binaryFunctionNo = intToBinary(tempInstruct.getFunctionNumber());
        stringBuilder += reverseString(binaryFunctionNo);
        if(binaryFunctionNo.length() > bitsUsedForLineNo){
            throw FUNCTION_NUMBER_TO_LARGE_FOR_BITS_DEFINED;
        }
        spacingNeeded = (bitsUsedForFunctionNo + bitsNotUsedAfterFunctionNumber) - (int)binaryFunctionNo.length();
        for(int x = 0; x < spacingNeeded; x++){
            stringBuilder += '0';
        }

        outputFile << stringBuilder << endl; //output line to file
    }

    // for each variable in variable container
    for(int i = 0; i < variableContainer.sizeOfVariableList(); i++){

        outputFile << reverseString(toBinary(variableContainer.getVariable(i).getVariableValue())) << endl;
    }

}

/**
 * Debugging tool to print out the processedInput vector
 */
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

/**
int main(){
    setup();
    printConfig();
    processInputFiles("test.txt");
    processAssembly();
    try {
        outputMachineCode("output.txt");
    }catch(int& e){
        cout << "exception: " << e << endl;
    }

}
 */

int main(){
    setup();
    printConfig();
    cout << "New config" << endl;
    updateConfig("config.txt");
    configMnemonicsAndFunctionNumbers("config.txt");
    printConfig();
}

