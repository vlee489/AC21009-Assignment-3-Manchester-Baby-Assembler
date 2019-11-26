//
// Holds functions for the assembler
//
#include "config.hpp"
#include "error.hpp"

#ifndef MBASSEMBLER_ASSEMBLERFUNCTIONS_HPP
#define MBASSEMBLER_ASSEMBLERFUNCTIONS_HPP

/**
 * Turns mnemonic into function numbers
 * @param mnemonic
 * @return the function number
 */
int mnemonicToInt(string mnemonic){
    if(mnemonic == "JMP"){
        return 0;
    }else if(mnemonic == "JRP"){
        return 1;
    }else if(mnemonic == "LDN"){
        return 2;
    }else if(mnemonic == "STO"){
        return 3;
    }else if(mnemonic == "SUB"){
        return 4;
    }else if(mnemonic == "CMP"){
        return 6;
    }else if(mnemonic == "STP"){
        return 7;
    }else{
        throw INSTRUCTION_DOES_NOT_EXIST;
    }
}

#endif //MBASSEMBLER_ASSEMBLERFUNCTIONS_HPP
