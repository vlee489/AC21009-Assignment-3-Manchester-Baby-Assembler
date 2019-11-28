//
// Constrains error codes that can be thrown by
// the assembler
//

#ifndef MBASSEMBLER_ERROR_HPP
#define MBASSEMBLER_ERROR_HPP

#include <string>
using namespace std;

// Error for label bank
#define LONG_VALUE_TO_LARGE -101 // When the Long is > 32 bits large
#define OUT_OF_MEMORY_RANGE -102 // When the memory location is outside the bank of 32 locations
#define VARIABLE_NAME_PRESENT -103 // When a variable already exists of the same name.
#define VARIABLE_DOES_NOT_EXIST -104 // When a variable doesn't exist
#define NOT_ENOUGH_MEMORY -105 // If there isn't enough memory Locations to be allocated out to all variables

// Errors for instructions
#define INSTRUCTION_DOES_NOT_EXIST  -301 // Instruction does not exist in instruction Set
#define OUTSIDE_OF_VECTOR_RANGE -302 // When an item is requested from an invalid vector location;
#define LABEL_ALREADY_EXISTS -303 // when you try to assign a instruction with a label that is already used

#define INPUT_TOO_BIG -401 // When the input int/long is too large

// Assembler errors
#define NO_INSTRUCTION_TO_PROCESS -501 // no instructions in vector to process
#define UNABLE_TO_FIND_START_OR_AND_END -502 // unable to find mnomics START or/and END
#define INPUT_PROCESS_FAILED -503 // Some error with processing the input of split varibles
#define INVALID_INPUT -504 // Invalid parm given
#define FILE_IO_ERROR -505 // can't open file
#define VARIABLE_USED_BUT_NOT_DEFINED -506 //when a variable is used but not defined in the assembly
#define MISS_MATCHING_VECTOR -507 // When the lines configuring the mnemoics and functions numbers aren't the same length
#define LINE_NUMBER_TO_LARGE_FOR_BITS_DEFINED -508 //When the line Number takes more bits then the number of bits allocated in it in config.hpp
#define FUNCTION_NUMBER_TO_LARGE_FOR_BITS_DEFINED -509 //When the function Number takes more bits then the number of bits allocated in it in config.hpp
#define INVALID_CHAR_IN_CONFIG -510 //When there's a invalid char in the config file, e.g when you have a non decimal number when defining the function numbers
#define MISSMATCHED_CONFIG_DETAILS -511 //When parts of config don't match, mainly numberOfInstructionsConfig and the number of mnemonics stated

/**
 * Explains the error
 * @param e the error code
 */
void explainError(int e){
    cout << "~~~~~~~~~~~~~" << endl;
    cout << "  meaning" << endl;
    switch(e){
        case -101 :
            cout << "Value too big for the memory size" << endl;
            cout << "value passed through is too big to fit in the available memory size." << endl;
            break;
        case -102 :
            cout << "Out of Memory Range" << endl;
            cout << "requested data from a memory location that doesn't exist" << endl;
            break;
        case -103 :
            cout << "Variable Name Present" << endl;
            cout << "you've defined a variable already and you try to define it again" << endl;
            break;
        case -104 :
            cout << "Variable Doesn't Exist" << endl;
            cout << "you use a variable with an instruction that you haven't defined" << endl;
            break;
        case -105 :
            cout << "Not Enough Memory" << endl;
            cout << "When there isn't enough memory locations to the number of Variables and Instructions." << endl;
            break;
        case -301 :
            cout << "Instruction Doesn't Exist" << endl;
            cout << "Assembly used a Instruction that doesn't exist in the instruction Set" << endl;
            break;
        case -302 :
            cout << "Vector Out of Range" << endl;
            cout << "assembler looked at an non-existent vector location" << endl;
            cout << "This is likely the programmer's fault" << endl;
            break;
        case -303 :
            cout << "Label Already Exists" << endl;
            cout << "You've used a label on a instruction/assembly line twice" << endl;
            break;
        case -401 :
            cout << "Input too big" << endl;
            cout << "input int/long is too big for function" << endl;
            break;
        case -501 :
            cout << "No Instruction to process" << endl;
            cout << "Assembler can't find instructions to process in the assembly file" << endl;
            break;
        case -502 :
            cout << "Unable to find START or END markers" << endl;
            cout << "Can't find the `START` or/and `END` markers in the assembly file" << endl;
            cout << "This error was deprecated in commit : d3ecd1616640e4163a91aeaf2d334c55b978d2c6" << endl;
            break;
        case -503 :
            cout << "Input Process Failed" << endl;
            cout << "Assembler failed to input you assembly file into it's data structure" << endl;
            break;
        case -504 :
            cout << "Invalid Input" << endl;
            cout << "invalid parameter given" << endl;
            break;
        case -505 :
            cout << "File IO Error" << endl;
            cout << "There was an error opening your text file." << endl;
            break;
        case -506 :
            cout << "Variable used but not defined" << endl;
            cout << "When one of your instruction in your assembly file is used but not defined" << endl;
            break;
        case -507 :
            cout << "Mis-Matched vectors" << endl;
            cout << "When you custom mnemonics and functionNumbers in your config text file don't have the same number of items in each to match up." << endl;
            break;
        case -508 :
            cout << "Line number too large for bits defined" << endl;
            cout << "When the line number of a variable is too large for the number of bits defined to hold the bits in machine code." << endl;
            break;
        case -509 :
            cout << "Function Number too large for bits defined" << endl;
            cout << "When the function number of a variable is too large for the number of bits defined to hold the bits in machine code." << endl;
            break;
        case -510 :
            cout << "Invalid char in config file" << endl;
            cout << "When there's a invalid char in the config file, e.g when you have a non decimal number when defining the function numbers" << endl;
            break;
        case -511 :
            cout << "Mis-matched config details" << endl;
            cout << "When parts of config don't match, mainly numberOfInstructionsConfig and the number of mnemonics stated" << endl;
            break;
        default :
            cout << "Not a standard error code " << endl;
            break;
    }
}

#endif //MBASSEMBLER_ERROR_HPP
