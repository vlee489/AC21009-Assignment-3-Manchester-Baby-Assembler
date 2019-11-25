//
// This class hold the data for each instruction
// that is to be output to machine code
//

#ifndef MBASSEMBLER_INSTRUCTION_HPP
#define MBASSEMBLER_INSTRUCTION_HPP

#include <string>
#include <utility>
#include "error.hpp"
#include "config.hpp"

using namespace std;

class instruction{
    string variable;
    int functionNumber;
    int memoryLocation;

public:
    instruction();
    instruction(string, int);
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
instruction::instruction() {
    this->variable = "";
    this->functionNumber = -1;
    this->memoryLocation = -1;
}

/**
 * Constructor but allows both fields to be set
 * @param lineInput what the Line Number should be set to
 * @param functionInput what the Function Number should be set to
 */
instruction::instruction(string variableInput, int functionInput) {
    // Checks weather the function that us being set exists
    if(functionInput < 0 || functionInput > numberOfInstructionsConfig){
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
void instruction::setFunctionNumber(int functionInput) {
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
int instruction::getFunctionNumber() {
    return this->functionNumber;
}

/**
 * Sets the fields of an object
 * @param lineInput what the Line Number should be set to
 * @param functionInput what the Function Number should be set to
 */
void instruction::setData(string variableInput, int functionInput) {
    // Checks weather the function that us being set exists
    if(functionInput < 0 || functionInput > numberOfMemoryLocationsConfig){
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
    this->variable = std::move(variableInput);
    this->functionNumber = functionInput;
}

/**
 * Sets the memoryLocation of the object
 * @param memoryInput what the memory location should be set to
 */
void instruction::setMemoryLocation(int memoryInput) {
    // check if the set memory location is within range
    if(memoryInput > (numberOfMemoryLocationsConfig-1) || memoryInput < 0){
        throw OUT_OF_MEMORY_RANGE;
    }
    this->memoryLocation = memoryInput;
}

/**
 * Gets the memory location of object
 * @return the memory location of the object requested
 */
int instruction::getMemoryLocation() {
    return this->memoryLocation;
}


#endif //MBASSEMBLER_INSTRUCTION_HPP
