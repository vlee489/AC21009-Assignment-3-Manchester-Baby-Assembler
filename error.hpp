//
// Constrains error codes that can be thrown by
// the assembler
//

#ifndef MBASSEMBLER_ERROR_HPP
#define MBASSEMBLER_ERROR_HPP

// Everything is awesome
#define SUCCESS 0

// Error for variable bank
#define LONG_VALUE_TO_LARGE -101 // When the Long is > 32 bits large
#define OUT_OF_MEMORY_RANGE -102 // When the memory location is outside the bank of 32 locations
#define VARIABLE_NAME_PRESENT -103 // When a variable already exists of the same name.


#endif //MBASSEMBLER_ERROR_HPP
