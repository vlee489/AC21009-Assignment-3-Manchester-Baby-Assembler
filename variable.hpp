//
// This header stuct defines an object for storing variables for the compiler
//
#ifndef AC21009_ASSIGNMENT_3_MANCHESTER_BABY_ASSEMBLER_VARIABLE_HPP
#define AC21009_ASSIGNMENT_3_MANCHESTER_BABY_ASSEMBLER_VARIABLE_HPP

#include <string>
#include <utility>
#include "error.hpp"

using namespace std;

class variable {
    string variableName; //Stores the name of the variable
    long variableValue; //Stores the value of the variable
    int memoryLocation; //Stores the memory location it will be placed in after assembling;
    /*
     * If memory location is set to -1 it means a memoryLocation hasn't been assigned
     */

public:
    variable(); // Default constructor
    variable(string, long); // Constructor allowing variable name and value to be set
    string getVariableName(){ return variableName;} //getter
    long getVariableValue(){ return variableValue;} //getter
    int getMemoryLocation(){ return memoryLocation;} //getter
    void setVariableName(string x){this->variableName = std::move(x);} //setter
    void setVariableValue(long);//setter
    void setMemoryLocation(int); //setter
    void assign(string, long); //`Assigner
    void assign(string, long, int); //`Assigner
};

/**
 * Default constructor
 */
variable::variable() {
    this->variableValue = 0;
    this->variableName = "";
    this->memoryLocation = -1;
}

/**
 * Default Constructor
 * @param inputString string to be set
 * @param inputLong The Long to be set
 */
variable::variable(string inputString, long inputLong) {
    if(inputLong > 4294967295){
        throw LONG_VALUE_TO_LARGE;
    }
    this->variableName = std::move(inputString);
    this->variableValue = inputLong;
    this->memoryLocation = -1;
}

/**
 * Sets the memory location
 * @param inputMemory memory location the variable should be placed into
 */
void variable::setMemoryLocation(int inputMemory) {
    if(inputMemory > 31){
        throw OUT_OF_MEMORY_RANGE;
    }else{
        this->memoryLocation = inputMemory;
    }
}

/**
 * Sets the variable's value
 * @param inputLong The Long to be set
 */
void variable::setVariableValue(long inputLong) {
    if(inputLong > 4294967295){
        throw LONG_VALUE_TO_LARGE;
    }else{
        this->variableValue = inputLong;
    }
}

/**
 * Assigns data to object
 * @param inputString string to be set
 * @param inputLong The Long to be set
 * @param inputMemory memory location the variable should be placed into
 */
void variable::assign(string inputString, long inputLong, int inputMemory) {
    if(inputMemory > 31){
        throw OUT_OF_MEMORY_RANGE;
    }
    if(inputLong > 4294967295){
        throw LONG_VALUE_TO_LARGE;
    }
    this->variableName = std::move(inputString);
    this->variableValue = inputLong;
    this->memoryLocation = inputMemory;
}

/**
 * Assigns data to object
 * @param inputString string to be set
 * @param inputLong The Long to be set
 */
void variable::assign(string inputString, long inputLong) {
    if(inputLong > 4294967295){
        throw LONG_VALUE_TO_LARGE;
    }
    this->variableName = std::move(inputString);
    this->variableValue = inputLong;
}


#endif //AC21009_ASSIGNMENT_3_MANCHESTER_BABY_ASSEMBLER_VARIABLE_HPP
