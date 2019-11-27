//
// This class is used for storing the list of instructions
//

#ifndef MBASSEMBLER_INSTRUCTIONLIST_HPP
#define MBASSEMBLER_INSTRUCTIONLIST_HPP

#include "instruction.hpp"
#include <utility>
#include <vector>
#include "error.hpp"
#include "config.hpp"

using namespace std;

class instructionList{
    vector<instruction> instructionList;

public:
    long getInstructionListSize(){ return instructionList.size();} // returns size of vector
    instruction getItemInInstructionList(int);
    void addInstructions(string, int);
    void addInstructions(int);
    void bulkSetMemoryLocation(int);
    void printInstructionList();
};

/**
 * gets an instruction object from the vector
 * @param vectorLocation vector locations
 * @return the instruction object requested
 */
instruction instructionList::getItemInInstructionList(int vectorLocation) {
    // Check whether the location is valid for the vector
    if(vectorLocation > (int)instructionList.size() || vectorLocation < 0) {
        throw OUTSIDE_OF_VECTOR_RANGE;
    }
    return instructionList.at(vectorLocation);
}

/**
 * Adds instruction to vector
 * @param variableName the variable name used
 * @param functionCode the function code of that instruction
 */
void instructionList::addInstructions(string variableName, int functionCode) {
    // creates object and places into vector
    instruction temp(std::move(variableName), functionCode);
    instructionList.push_back(temp);
}

/**
 * Adds instruction to vector
 * @param functionCode the function code of that instruction
 */
void instructionList::addInstructions(int functionCode) {
    // creates object and places into vector
    instruction temp(functionCode);
    instructionList.push_back(temp);
}

/**
 * Allows for bulk setting memory locations
 * @param fromMemoryLocation the memory location to start from
 */
void instructionList::bulkSetMemoryLocation(int fromMemoryLocation) {
    // Checks if we have enough memory locations to allocate to all variables
    if((numberOfMemoryLocationsConfig-fromMemoryLocation) < (int)instructionList.size()){
        throw NOT_ENOUGH_MEMORY;
    }else{
        int memoryLocationBeingSet = fromMemoryLocation;
        // for each instruction we set the memory location then increment the instruction by one
        for(auto & i : instructionList){
            i.setMemoryLocation(memoryLocationBeingSet);
            memoryLocationBeingSet++;
        }
        return;
    }
}

/**
 * Prints out the list of all instructions
 */
void instructionList::printInstructionList() {
    cout << "==========================" << endl;
    cout << "Instruction Vector List" << endl;
    for(auto & i : instructionList){
        cout << "Function Number : " << i.getFunctionNumber() << " | Variable Used: " << i.getVariable() << " | Memory Address: " << i.getMemoryLocation() << endl;
    }
    cout << "==========================" << endl;
}

#endif //MBASSEMBLER_INSTRUCTIONLIST_HPP
