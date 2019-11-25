//
// This is shared code between the Assembler
// and the Manchester Baby computer
//

#ifndef MBASSEMBLER_SHAREDLIBRARY_HPP
#define MBASSEMBLER_SHAREDLIBRARY_HPP

#include <bitset>

/**
 * Truns a long into a binary output
 * @param longInput the long you want a boolean version of
 * @return the string containing 1/0
 */
string toBinary(long longInput){
    return bitset<32>(longInput).to_string();
}

/**
 * Turns number into 3 bits
 * @param inputInt input number
 * @return string binary
 */
string instructionToBinary(int inputInt){
    if(inputInt > 7){
        throw INPUT_TOO_BIG;
    }
    return bitset<3>(inputInt).to_string();
}

/**
 * Reverses a string
 * @param stringIn string to be reversed
 * @return the reversed string
 */
string reverseString(string stringIn){
    string temp = stringIn;
    reverse(temp.begin(), temp.end());
    return temp;
}


#endif //MBASSEMBLER_SHAREDLIBRARY_HPP
