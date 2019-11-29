//
// This class is used for storing variables that come in.
//  Pui-Hin Vincent Lee: 180006178
//  Alina Littek: 180016182
//  Bjarne Kopplin: 180016866
//	Jacque Nalwanga: 180004882
//	Andrew Spence: 170018476
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
    variable getVariable(int vectorLocation);
};

/**
 * Checks if a variable with that name already exists
 * @param variableName the name you want to see is in the list or not
 * @return whether the item exists or not
 */
bool variableList::doesContainName(const string& variableName) {
    // We look through each item in the vector
    for(auto & i : variableContainer){
        if(i.getVariableName() == variableName){ //if the object we have a name matching
            return true;// we return true as the object exists
        }
    }
    return false; // if we go through the whole vector with no valid responses we return false for no doesn't exist
}

/**
 * Adds a variable to the list
 * @param variableName name of the variable to be added
 * @param variableLong the size of the variable.
 */
void variableList::addVariable(string variableName, long variableLong) {
    if(!doesContainName(variableName)){
        variable temp; //create object
        temp.assign(variableName, variableLong); //set values
        variableContainer.push_back(temp); // place object into vector
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
        //for each variable object in the vector
        for(auto & i : variableContainer){
            if(i.getVariableName() == variableName){// if the variables name match
                i.setVariableValue(variableLong);//set the variable value of object
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
        //for each variable object in the vector
        for(auto & i : variableContainer){
            if(i.getVariableName() == variableName){// if the variables name match
                i.setMemoryLocation(memoryLocation);// set the memory location of the object
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
            i.setMemoryLocation(memoryLocationBeingSet); // set memory location
            memoryLocationBeingSet++; //increment the memory location being set
            // if we have too many variables for after the instructions we use location 0 to store a variable
            if(memoryLocationBeingSet == numberOfMemoryLocationsConfig){
                memoryLocationBeingSet = 0;
            }
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
        //for each variable object in the vector
        for(auto & i : variableContainer){
            if(i.getVariableName() == variableName){ // if the variables name match
                return i.getVariableValue(); //return the variable value of object
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
        //for each variable object in the vector
        for(auto & i : variableContainer){
            if(i.getVariableName() == variableName){ // if the variables name match
                return i.getMemoryLocation(); // return the memory location of the object
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
    for(auto & i : variableContainer){ // for each item in the vector
        cout << "Variable Name: " << i.getVariableName() << " | Variable Value: " << i.getVariableValue() << " | Memory Address: " << i.getMemoryLocation() << endl;
    }
    cout << "==========================" << endl;
}

/**
 * returns the variable object
 * @param vectorLocation the vector locations
 * @return the variable object from the requested object location.
 */
variable variableList::getVariable(int vectorLocation) {
    if(vectorLocation > (int)variableContainer.size() || vectorLocation < 0){
        throw OUTSIDE_OF_VECTOR_RANGE;
    }
    return variableContainer.at(vectorLocation);
}


#endif //MBASSEMBLER_VARIABLELIST_HPP
