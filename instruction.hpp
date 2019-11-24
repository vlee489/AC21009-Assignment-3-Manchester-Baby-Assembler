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
    int lineNumber;
    int functionNumber;

public:
    instructions();
    instructions(int, int);
    void setData(int, int);
    void setLineNumber(int);
    void setFunctionNumber(int);
    int getLineNumber();
    int getFunctionNumber();
};

/**
 * Default constructor
 */
instructions::instructions() {
    this->lineNumber = -1;
    this->functionNumber = -1;
}

/**
 * Constructor but allows both fields to be set
 * @param lineInput what the Line Number should be set to
 * @param functionInput what the Function Number should be set to
 */
instructions::instructions(int lineInput, int functionInput) {
    // Checks whether a memory location an instruction wants to access exists.
    if(lineInput > 31 || lineInput < 0){
        throw OUT_OF_MEMORY_RANGE;
    }
    // Checks weather the function that us being set exists
    if(functionInput < 0 || functionInput > 7){
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
    this->lineNumber = lineInput;
    this->functionNumber = functionInput;
}

/**
 * Sets the line number of the object
 * @param lineInput what the Line Number should be set to
 */
void instructions::setLineNumber(int lineInput) {
    // Checks whether a memory location an instruction wants to access exists.
    if(lineInput > 31 || lineInput < 0){
        throw OUT_OF_MEMORY_RANGE;
    }
    this->lineNumber = lineInput;
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
 * Gets the line number of the object
 * @return the line number requested from the object
 */
int instructions::getLineNumber() {
    return this->lineNumber;
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
void instructions::setData(int lineInput, int functionInput) {
    // Checks whether a memory location an instruction wants to access exists.
    if(lineInput > 31 || lineInput < 0){
        throw OUT_OF_MEMORY_RANGE;
    }
    // Checks weather the function that us being set exists
    if(functionInput < 0 || functionInput > 7){
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
    this->lineNumber = lineInput;
    this->functionNumber = functionInput;
}


#endif //MBASSEMBLER_INSTRUCTION_HPP
