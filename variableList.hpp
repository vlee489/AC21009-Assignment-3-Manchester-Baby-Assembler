//
// This class is used for storing variables that come in.
//

#ifndef MBASSEMBLER_VARIABLELIST_HPP
#define MBASSEMBLER_VARIABLELIST_HPP

#include <vector>
#include "variable.hpp"
#include "error.hpp"
#include "config.hpp"

using namespace std;

class variableList{
    vector<variable> variableContainer; // Contains the variables
public:
    // Look below the class declaration for the use of each function
    bool doesContainName(const string& variableName);
    void addVariable(string variableName, long variableLong);
    void updateVariable(string variableName, long variableLong);
    void setMemoryLocation(string variableName, int memoryLocation);
    void bulkSetMemoryLocation(int fromMemoryLocation);
    long getVariableData(string variableName);
    int getMemoryLocation(string variableName);
    int sizeOfVariableList();
    void printVariableList();
};

/**
 * Checks if a variable with that name already exists
 * @param variableName the name you want to see is in the list or not
 * @return wether the item exists or not
 */
bool variableList::doesContainName(const string& variableName) {
    for(auto & i : variableContainer){
        if(i.getVariableName() == variableName){
            return true;
        }
    }
    return false;
}

/**
 * Adds a variable to the list
 * @param variableName name of the variable to be added
 * @param variableLong the size of the variable.
 */
void variableList::addVariable(string variableName, long variableLong) {
    if(!doesContainName(variableName)){
        variable temp;
        temp.assign(variableName, variableLong);
        variableContainer.push_back(temp);
    }else{
        throw VARIABLE_NAME_PRESENT;
    }
}

/**
 * Updates the value of a variable
 * @param variableName name of variable to update
 * @param variableLong the size of the variable.
 */
void variableList::updateVariable(string variableName, long variableLong) {
    if(doesContainName(variableName)){
        for(auto & i : variableContainer){
            if(i.getVariableName() == variableName){
                i.setVariableValue(variableLong);
                return;
            }
        }
    }else{
        throw VARIABLE_DOES_NOT_EXIST;
    }
}

/**
 * Sets the memory location of a variable
 * @param variableName name of variable to update
 * @param memoryLocation memory location 0-31 to set
 */
void variableList::setMemoryLocation(string variableName, int memoryLocation) {
    if(doesContainName(variableName)){
        for(auto & i : variableContainer){
            if(i.getVariableName() == variableName){
                i.setMemoryLocation(memoryLocation);
                return;
            }
        }
    }else{
        throw VARIABLE_DOES_NOT_EXIST;
    }
}

/**
 * Allows for bulk setting of memory addresses of the whole list
 * @param fromMemoryLocation memory address to set from
 */
void variableList::bulkSetMemoryLocation(int fromMemoryLocation) {
    // Checks if we have enough memory locations to allocate to all variables
    if((numberOfMemoryLocationsConfig-fromMemoryLocation) < (int)variableContainer.size()){
        throw NOT_ENOUGH_MEMORY;
    }else{
        int memoryLocationBeingSet = fromMemoryLocation;
        for(auto & i : variableContainer){
            i.setMemoryLocation(memoryLocationBeingSet);
            memoryLocationBeingSet++;
        }
        return;
    }
}

/**
 * Returns the variable data
 * @param variableName name of variable to check from
 * @return the variable data
 */
long variableList::getVariableData(string variableName) {
    if(!doesContainName(variableName)){
        throw VARIABLE_DOES_NOT_EXIST;
    }else{
        for(auto & i : variableContainer){
            if(i.getVariableName() == variableName){
                return i.getVariableValue();
            }
        }
    }
    throw VARIABLE_DOES_NOT_EXIST;
}

/**
 * Returns the memory location of an item
 * @param variableName name of variable to check from
 * @return the memory location of the variable
 */
int variableList::getMemoryLocation(string variableName) {
    if(!doesContainName(variableName)){
        throw VARIABLE_DOES_NOT_EXIST;
    }else{
        for(auto & i : variableContainer){
            if(i.getVariableName() == variableName){
                return i.getMemoryLocation();
            }
        }
    }
    throw VARIABLE_DOES_NOT_EXIST;
}

/**
 * Returns the size of the list of variables
 * @return size of the list of variables
 */
int variableList::sizeOfVariableList() {
    return (int)variableContainer.size();
}

/**
 * Prints out the list of variables to the console
 */
void variableList::printVariableList() {
    cout << "==========================" << endl;
    cout << "Variable Vector List" << endl;
    for(auto & i : variableContainer){
        cout << "Variable Name: " << i.getVariableName() << " | Variable Value: " << i.getVariableValue() << " | Memory Address: " << i.getMemoryLocation() << endl;
    }
    cout << "==========================" << endl;
}


#endif //MBASSEMBLER_VARIABLELIST_HPP
