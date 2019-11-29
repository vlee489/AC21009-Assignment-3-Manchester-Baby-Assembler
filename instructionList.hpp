//
// This class is used for storing the list of instructions
//  Pui-Hin Vincent Lee: 180006178
//  Alina Littek: 180016182
//  Bjarne Kopplin: 180016866
//	Jacque Nalwanga: 180004882
//	Andrew Spence: 170018476
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
    bool doesLabelExist(string);
    long getInstructionListSize(){ return instructionList.size();} // returns size of vector
    instruction getItemInInstructionList(int);
    void addInstructions(string, int, const string&);
    void addInstructions(string, int);
    void addInstructions(int);
    void bulkSetMemoryLocation(int);
    void printInstructionList();
    instruction getInstuctionViaLabel(string label);
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
        for(auto & i : instructionList){ // for each object in vector
            i.setMemoryLocation(memoryLocationBeingSet); // set memeory address
            memoryLocationBeingSet++; // increment memory by one
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
    for(auto & i : instructionList){ // for each each object in vector
        cout << "Function Number : " << i.getFunctionNumber() << " | Variable Used: " << i.getVariable() << " | Memory Address: " << i.getMemoryLocation() << " | Label: " << i.getLabel() << endl;
    }
    cout << "==========================" << endl;
}

/**
 * Checks if labels exists in list already
 * @param labelInput the label to check for
 * @return true if it exists, else false
 */
bool instructionList::doesLabelExist(string labelInput) {
    for(auto &item : instructionList){ // for each object in vector
        if(item.getLabel() == labelInput && !item.getLabel().empty()){ // if we get a match and the label isn't empty
            return true;
        }
    }
    return false;
}



/**
 * Adds instruction to vector with label
 * @param variableName the variable name used
 * @param functionCode the function code of that instruction
 * @param labelInput the label to set to that instruction line
 */
void instructionList::addInstructions(string variableName, int functionCode, const string& labelInput) {
    // checks if item wti the same label exists already
    if(doesLabelExist(labelInput)){
        throw LABEL_ALREADY_EXISTS;
    }
    // creates object and places into vector
    instruction temp(variableName, functionCode, labelInput);
    instructionList.push_back(temp);
}

/**
 * Returns the instruction by looking for the label attached to it
 * @param label the label being looked for
 * @return the instruction object needing to be returned
 */
instruction instructionList::getInstuctionViaLabel(string label) {
    // we check if the label exists, if it doesn't we throw an error
    if(!doesLabelExist(label)){
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
    for(auto &item : instructionList){ //looks through each object in vector
        if(item.getLabel() == label){ //if we find the label matching
            return item; //return the object
        }
    }
    throw INSTRUCTION_DOES_NOT_EXIST; // throw an error if we can't find a matching object
}

#endif //MBASSEMBLER_INSTRUCTIONLIST_HPP
