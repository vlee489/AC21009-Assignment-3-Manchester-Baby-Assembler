//
// Main file that runs the assembler
//  Pui-Hin Vincent Lee: 180006178
//  Alina Littek: 180016182
//  Bjarne Kopplin: 180016866
//	Jacque Nalwanga: 180004882
//	Andrew Spence: 170018476
//

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <limits>
#include <cstring>
#include "error.hpp"
#include "variableList.hpp"
#include "sharedLibrary.hpp"
#include "instructionList.hpp"

using namespace std;

vector<vector<string>> processedInput; // Holds the input file after it's cleaned up
variableList variableContainer; // Holds all the variables used in the assembly file AKA Symbol table
instructionList instructionContainer; // Holds all the instructions states in the assembly file
const string arrayMnemonics[8] = {"JMP", "JRP", "LDN", "STO", "SUB", "CMP", "STP", "MTP"};
const int arrayFunctionNo[8] = {0, 1, 2, 3, 4, 6, 7, 8};

vector<string> mnemonics;
vector<int> functionNumbers;

/**
 * sets up program vectors
 */
void setup() {
    //places the mnemonic and function Numbers from their arrays into their vectors
    for (auto &item : arrayMnemonics) { // for each item in array
        mnemonics.push_back(item); //place that ite into the vector
    }
    for (auto &item : arrayFunctionNo) { // for each item in array
        functionNumbers.push_back(item); //place that ite into the vector
    }
}

/**
 * Allows for setting custom mnemonics and function numbers via a config txt file
 * @param configFile the config txt file to go off of.
 */
void configMnemonicsAndFunctionNumbers(string configFile) {
    //open file
    ifstream reader(configFile);

    //check it has opened correctly
    if (!reader) {
        cout << "Error opening config file" << endl;
        throw FILE_IO_ERROR;
    }

    string line;
    while (getline(reader, line)) {    // read file line by line
        string option;
        //gets the option out
        for (auto &c : line) {
            if (c == ':') {
                break;
            } else {
                option += c;
            }
        }

        if (option == "mnemonics") { //if we find the keyword
            mnemonics.clear();
            string newMnemonics = "";
            bool startOfInput = false;
            //This gets all the chars between the backets in the config file
            for (auto &c : line) {
                if (c == '[') {
                    startOfInput = true;
                } else if (startOfInput && c != ']') {
                    newMnemonics += c;
                } else if (c == ']') {
                    break;
                }
            }
            stringstream mnemonicsStream(newMnemonics);
            string temp;
            //splits out the mnemonics into the vector
            while (getline(mnemonicsStream, temp, ' ')) {
                mnemonics.push_back(temp); // place the mnemonics into vector
            }
        } else if (option == "functionNumbers") {
            functionNumbers.clear();
            string newFunctionNo = "";
            bool startOfInput = false;
            //This gets all the chars between the backets in the config file
            for (auto &c : line) {
                if (c == '[') {
                    startOfInput = true;
                } else if (startOfInput && c != ']') {
                    newFunctionNo += c;
                } else if (c == ']') {
                    break;
                }
            }
            stringstream functionNoStream(newFunctionNo);
            string temp;
            //splits function numbers into function number
            while (getline(functionNoStream, temp, ' ')) {
                try {
                    functionNumbers.push_back(stoi(temp)); // place the mnemonics into vector
                } catch (...) {
                    throw INVALID_CHAR_IN_CONFIG; // we find char that isn't a decimal in the option
                }
            }
        }
    }
    // Checks if the size of both vectors are the same
    if (mnemonics.size() != functionNumbers.size()) {
        throw MISS_MATCHING_VECTOR;
    }

    //checks if numberOfInstructionsConfig and number of mnemonics match
    if (numberOfInstructionsConfig != (int) mnemonics.size()) {
        throw MISSMATCHED_CONFIG_DETAILS;
    }
}

/**
 * Prints out config and the mnemonics and function Number combos
 */
void printConfig() {
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
    for (int loc = 0; loc < (int) mnemonics.size(); loc++) {
        cout << mnemonics.at(loc) << " | " << functionNumbers.at(loc) << endl;
    }
    cout << "================================================" << endl;
}

/**
 * Turns mnemonic into function numbers
 * @param mnemonic
 * @return the function number
 */
int mnemonicToInt(const string &mnemonic) {

    // for each item in the mnemonics vector
    for (int loc = 0; loc < (int) mnemonics.size(); loc++) {
        // if the mnemonic we're looking for is in the mnemonics vector
        if (mnemonics.at(loc) == mnemonic) {
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
void processInputFiles(const string &txtFile) {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Reading in file into Assembly Code hold" << endl;

    ifstream reader(txtFile);

    //if nothing is passed in, we didn't get a valid input
    if (txtFile.empty()) {
        throw INVALID_INPUT;
    }

    if (!reader) {
        cout << "Error opening input file" << endl;
        throw FILE_IO_ERROR;
    }

    string line;
    while (getline(reader, line)) {
        cout << "reading line: " << line << endl;
        string chunk = ""; //Used to temp hold chars as we process them
        vector<string> tempVector; // creates a temp vector for holding strings
        for (char &l : line) { //
            if (l == ' ' && !chunk.empty()) {
                tempVector.push_back(chunk);
                chunk = "";
            } else if (l == ';') { // we break if we hit a comment as the semi-collon and anything after is a comment
                break;
            } else if (l != ':' && l != ' ') {
                chunk += l;
            }
        }
        if(!chunk.empty()){
            tempVector.push_back(chunk); //push the last item if there is one into the vector
        }
        // If the tempory vector for the line we just processed isn't empty we push it to the vector
        if (!tempVector.empty()) {
            processedInput.push_back(tempVector);
        }
    }
    reader.close(); // close the reader

    // Check if we have data to process.
    if (processedInput.empty()) {
        throw INPUT_PROCESS_FAILED;
    }

    cout << "Read file Successful" << endl;
}

/**
 * Processes the assembly file in the processedInput Vector into variable and instruction containers
 */
void processAssembly() {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Processing Assembly Code into instruction and symbol table" << endl;

    // check if there's stuff to process
    if (processedInput.empty()) {
        throw NO_INSTRUCTION_TO_PROCESS;
    }

    for (auto &line : processedInput) { // for each line in assembly
        vector<string> vectorTemp = line; // This variable is a temp holding locations for the line we're processing at the time.
        // temp strings to hold the data while we fetch it
        string variableName = "";
        string mnemonicName = "";
        string label = "";
        string varValue = "";
        //Prints out the line we're on
        for (auto &item : vectorTemp) {
            cout << item << " | "; //prints out every item in vector
        }


        if (find(mnemonics.begin(), mnemonics.end(), vectorTemp.at(0)) != mnemonics.end()) {
            // If we find a mnemonic in the first work
            if (1 < (int) vectorTemp.size()) {
                variableName = vectorTemp.at(1);
            }
            if (!vectorTemp.empty()) {
                mnemonicName = vectorTemp.at(0);
            }
            instructionContainer.addInstructions(variableName, mnemonicToInt(mnemonicName)); // place instruction
            cout << "entered | ";
        } else if ((int) vectorTemp.size() > 1) {
            if (vectorTemp.at(1) == "VAR") {
                // if we find a variable
                if (2 < (int) vectorTemp.size()) {
                    varValue = vectorTemp.at(2);
                }
                if (!vectorTemp.empty()) {
                    mnemonicName = vectorTemp.at(0);
                }
                // if line contains variable
                variableContainer.addVariable(mnemonicName, stoi(varValue)); // add variables
                cout << "entered | ";
            } else if (find(mnemonics.begin(), mnemonics.end(), vectorTemp.at(1)) != mnemonics.end()) {
                //if we find a mnemonic with a label
                if (2 < (int) vectorTemp.size()) {
                    variableName = vectorTemp.at(2);
                }
                if (1 < (int) vectorTemp.size()) {
                    mnemonicName = vectorTemp.at(1);
                }
                if (!vectorTemp.empty()) {
                    label = vectorTemp.at(0);
                }
                instructionContainer.addInstructions(variableName, mnemonicToInt(mnemonicName), label); // place instruction
                cout << "entered | ";
            }
        }
        cout << endl;
    }

    // This assigns the memory locations of the instructions.
    instructionContainer.bulkSetMemoryLocation(1); // this is set to 1 as the MB starts its IC from 1 instead of 0
    // This assigns the memory locations of the variables, from the last instructions
    // We bulk set the variable locations from the location after the instructions that will the size of the instruction Container +1
    variableContainer.bulkSetMemoryLocation((int) instructionContainer.getInstructionListSize() + 1);
    cout << "Completed processing items into Instruction and Symbol table" << endl;
}

/**
 * Re-asembles the Variable and Instruction containers into machine code
 * @param writeFile the file to output the machine code to.
 */
void outputMachineCode(const string &writeFile) {
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "Starting output of machine code to text file" << endl;
    if (variableContainer.sizeOfVariableList() == 0 || instructionContainer.getInstructionListSize() == 0) {
        throw INPUT_PROCESS_FAILED;
    }
    //if nothing is passed in, we didn't get a valid input
    if (writeFile.empty()) {
        throw INVALID_INPUT;
    }

    //opens file to write to it
    ofstream outputFile(writeFile);
    // we check if we opened the file correctly
    if (!outputFile.is_open()) {
        cout << "Error opening input file" << endl;
        throw FILE_IO_ERROR;
    }

    string stringBuilder = ""; // holds string to place into machine code output

    // if the variables and instruction to output to machine code are
    // less the the number of memory locations we start the first line as a 0s
    if ((int) variableContainer.sizeOfVariableList() + (int) instructionContainer.getInstructionListSize() <
        numberOfMemoryLocationsConfig - 1) {
        // we do a for loop for the total width of the memory
        int total = bitsNotUserAfterLineNo+bitsNotUsedAfterFunctionNumber+bitsUsedForLineNo+bitsUsedForFunctionNo;
        for(int i = 0; i < total; i++){
            stringBuilder+='0';
        }
        outputFile << stringBuilder << endl; // output string to txt file
        cout << "Outputting: " << stringBuilder << endl; // output line to console
        stringBuilder = "";
    }


    // for each instruction in the Instruction Container
    for (int i = 0; i < (int) instructionContainer.getInstructionListSize(); i++) {
        instruction tempInstruct = instructionContainer.getItemInInstructionList(i);
        stringBuilder = ""; // holds string to place into machine code output
        // Isn't a jump we process like normal
        int lineNo = 0;
        if(tempInstruct.getFunctionNumber() == jumpFunctionNumber){
            lineNo = instructionContainer.getInstuctionViaLabel(tempInstruct.getVariable()).getMemoryLocation();
        }else{
            try {
                lineNo = variableContainer.getMemoryLocation(tempInstruct.getVariable());
            } catch (...) {
                //This try catch is to catch any time we looks for a variable that doesn't exist,
                //like when the string is blank, e.g. STP command
                if (tempInstruct.getFunctionNumber() > 7 || tempInstruct.getFunctionNumber() < 6 ) { // we check if it's the stp function
                    throw VARIABLE_USED_BUT_NOT_DEFINED;
                }
            }
        }

        // get the line number and work out the binary version
        string binaryLineNo = intToBinary(lineNo);
        if ((int) binaryLineNo.length() > bitsUsedForLineNo) {
            throw LINE_NUMBER_TO_LARGE_FOR_BITS_DEFINED;
        }
        stringBuilder += reverseString(binaryLineNo); // places line number into the line output string
        // This for loop places the spacing between the line number and function number
        int spacingNeeded = (bitsUsedForLineNo + bitsNotUserAfterLineNo) - (int) binaryLineNo.length();
        // This actually places the 0s into the string
        for (int x = 0; x < spacingNeeded; x++) {
            stringBuilder += '0';
        }

        // get the function number and output it into the line output string
        string binaryFunctionNo = intToBinary(tempInstruct.getFunctionNumber());
        stringBuilder += reverseString(binaryFunctionNo);
        if ((int) binaryFunctionNo.length() > bitsUsedForLineNo) {
            throw FUNCTION_NUMBER_TO_LARGE_FOR_BITS_DEFINED;
        }
        spacingNeeded = (bitsUsedForFunctionNo + bitsNotUsedAfterFunctionNumber) - (int) binaryFunctionNo.length();
        // This actually places the 0s into the string
        for (int x = 0; x < spacingNeeded; x++) {
            stringBuilder += '0';
        }

        outputFile << stringBuilder << endl; //output line to file
        cout << "Outputting: " << stringBuilder << endl;// output line to console
    }

    // for each variable in variable container
    for (int i = 0; i < variableContainer.sizeOfVariableList(); i++) {
        string stringBuilder = reverseString(toBinary(variableContainer.getVariable(i).getVariableValue()));
        outputFile << stringBuilder << endl;//output line to file
        cout << "Outputting: " << stringBuilder << endl;// output line to console
    }

}

/**
 * Debugging tool to print out the processedInput vector
 */
void printVectorLine() {
    cout << "INPUT VECTOR" << endl;
    cout << "=======================" << endl;
    for (auto &i : processedInput) {
        cout << endl;
        for (auto &o : i) {
            cout << o << "|";
        }
    }
    cout << endl << "=======================" << endl;
}

int main(int argc, char *argv[]){
    setup();
    if(argc < 3){
        cout << "You need a min of 2 arguments" << endl;
        return -1;
    }
    //run assembler with file input/output
    if(argc == 3){
        string inputFile = argv[1];
        string outFile = argv[2];
        try {
            processInputFiles(inputFile);
            processAssembly();
            outputMachineCode(outFile);
            return 0;
        }catch(int& e){
            cout << "Looks like you've hit an error in the assembler" << endl;
            cout << "exception code: " << e << endl;
            explainError(e);
            return 0;
        }catch(exception& e){
            cout << "The assembler has hit into an standered error" << endl;
            cout << "Probably the assembler's programmer's fauly" << endl;
            cout << e.what() << endl;
            return 0;
        }
    }
    //run assembler with file input/output and a custom config
    if(argc == 4){
        string inputFile = argv[1];
        string outFile = argv[2];
        string configFile = argv[3];
        try {
            cout << "Updating config from Text file" << endl;
            updateConfig(configFile);
            configMnemonicsAndFunctionNumbers(configFile);
            cout << "Please check the new configuration" << endl;
            printConfig();
            cout << "Press Enter to Continue";
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            processInputFiles(inputFile);
            processAssembly();
            outputMachineCode(outFile);
            return 0;
        }catch(int& e){
            cout << "Looks like you've hit an error in the assembler" << endl;
            cout << "exception code: " << e << endl;
            explainError(e);
            return 0;
        }catch(exception& e){
            cout << "The assembler has hit into an standered error" << endl;
            cout << "Probably the assembler's programmer's fauly" << endl;
            cout << e.what() << endl;
            return 0;
        }
    }
    //run assembler with file input/output , custom config and dump all debug info to the console
    if(argc == 5 && strncmp(argv[4], "-d", 2) == 0){
        cout << "RUNNING WITH DEBUG INFO" << endl;
        string inputFile = argv[1];
        string outFile = argv[2];
        string configFile = argv[3];
        try {
            cout << "Updating config from Text file" << endl;
            updateConfig(configFile);
            configMnemonicsAndFunctionNumbers(configFile);
            printConfig();
            processInputFiles(inputFile);
            printVectorLine();
            processAssembly();
            instructionContainer.printInstructionList();
            variableContainer.printVariableList();
            outputMachineCode(outFile);
            return 0;
        }catch(int& e){
            cout << "Looks like you've hit an error in the assembler" << endl;
            cout << "exception code: " << e << endl;
            explainError(e);
            return 0;
        }catch(exception& e){
            cout << "The assembler has hit into an standered error" << endl;
            cout << "Probably the assembler's programmer's fauly" << endl;
            cout << e.what() << endl;
            return 0;
        }
    }

    cout << "Too Many Arguments/incorrect arguments" << endl;
    return -1;
}