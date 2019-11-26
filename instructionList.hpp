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

instruction instructionList::getItemInInstructionList(int vectorLocation) {
    // Check whether the location is valid for the vector
    if(vectorLocation > instructionList.size() || vectorLocation < 0) {
        throw OUTSIDE_OF_VECTOR_RANGE;
    }
    return instructionList.at(vectorLocation);
}

void instructionList::addInstructions(string variableName, int functionCode) {
    instruction temp(std::move(variableName), functionCode);
    instructionList.push_back(temp);
}

void instructionList::addInstructions(int functionCode) {
    instruction temp(functionCode);
    instructionList.push_back(temp);
}

void instructionList::bulkSetMemoryLocation(int fromMemoryLocation) {
    // Checks if we have enough memory locations to allocate to all variables
    if((numberOfMemoryLocationsConfig-fromMemoryLocation) < (int)instructionList.size()){
        throw NOT_ENOUGH_MEMORY;
    }else{
        int memoryLocationBeingSet = fromMemoryLocation;
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
