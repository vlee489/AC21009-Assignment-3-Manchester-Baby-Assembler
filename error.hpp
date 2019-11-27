//
// Constrains error codes that can be thrown by
// the assembler
//

#ifndef MBASSEMBLER_ERROR_HPP
#define MBASSEMBLER_ERROR_HPP

// Error for variable bank
#define LONG_VALUE_TO_LARGE -101 // When the Long is > 32 bits large
#define OUT_OF_MEMORY_RANGE -102 // When the memory location is outside the bank of 32 locations
#define VARIABLE_NAME_PRESENT -103 // When a variable already exists of the same name.
#define VARIABLE_DOES_NOT_EXIST -104 // When a variable doesn't exist
#define NOT_ENOUGH_MEMORY -105 // If there isn't enough memory Locations to be allocated out to all variables

// Errors for instructions
#define INSTRUCTION_DOES_NOT_EXIST  -301 // Instruction does not exist in instruction Set
#define OUTSIDE_OF_VECTOR_RANGE -302 // When an item is requested from an invalid vector location;

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

#endif //MBASSEMBLER_ERROR_HPP
