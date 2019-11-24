//
// This class hold the data for each instruction
// that is to be output to machine code
//

#ifndef MBASSEMBLER_INSTRUCTION_HPP
#define MBASSEMBLER_INSTRUCTION_HPP

#include <string>
#include <utility>
#include "error.hpp"

using namespace std;

class instructions{
    string variable;
    int functionNumber;
    int memoryLocation;

public:
    instructions();
    instructions(string, int);
    void setData(string, int);
    void setFunctionNumber(int);
    void setMemoryLocation(int);
    void setVariable(string variableInput){this->variable = std::move(variableInput);}
    int getFunctionNumber();
    int getMemoryLocation();
    string getVariable(){return this->variable;}
};

/**
 * Default constructor
 */
instructions::instructions() {
    this->variable = "";
    this->functionNumber = -1;
    this->memoryLocation = -1;
}

/**
 * Constructor but allows both fields to be set
 * @param lineInput what the Line Number should be set to
 * @param functionInput what the Function Number should be set to
 */
instructions::instructions(string variableInput, int functionInput) {
    // Checks weather the function that us being set exists
    if(functionInput < 0 || functionInput > 7){
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
    this->variable = std::move(variableInput);
    this->functionNumber = functionInput;
    this->memoryLocation = -1;
}

/**
 * Sets the function number of the object
 * @param functionInput what the Function Number should be set to
 */
void instructions::setFunctionNumber(int functionInput) {
    // Checks weather the function that us being set exists
    if(functionInput < 0 || functionInput > 7){
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
    this->functionNumber = functionInput;
}

/**
 * Gets the function number of the object
 * @return the function number of the object requested
 */
int instructions::getFunctionNumber() {
    return this->functionNumber;
}

/**
 * Sets the fields of an object
 * @param lineInput what the Line Number should be set to
 * @param functionInput what the Function Number should be set to
 */
void instructions::setData(string variableInput, int functionInput) {
    // Checks weather the function that us being set exists
    if(functionInput < 0 || functionInput > 7){
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
    this->variable = std::move(variableInput);
    this->functionNumber = functionInput;
}

/**
 * Sets the memoryLocation of the object
 * @param memoryInput what the memory location should be set to
 */
void instructions::setMemoryLocation(int memoryInput) {
    // check if the set memory location is within range
    if(memoryInput > 31 || memoryInput < 0){
        throw OUT_OF_MEMORY_RANGE;
    }
    this->memoryLocation = memoryInput;
}

/**
 * Gets the memory location of object
 * @return the memory location of the object requested
 */
int instructions::getMemoryLocation() {
    return this->memoryLocation;
}


#endif //MBASSEMBLER_INSTRUCTION_HPP
