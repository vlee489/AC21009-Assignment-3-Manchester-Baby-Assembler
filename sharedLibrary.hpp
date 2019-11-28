//
// This is shared code between the Assembler
// and the Manchester Baby computer
//

#ifndef MBASSEMBLER_SHAREDLIBRARY_HPP
#define MBASSEMBLER_SHAREDLIBRARY_HPP

#include <bitset>
#include <algorithm>

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
 * Turns number into 5 bits
 * @param inputInt input number
 * @return string binary
 */
string memoryLocationToBinary(int inputInt){
    if(inputInt > 31){
        throw INPUT_TOO_BIG;
    }
    return bitset<5>(inputInt).to_string();
}

/**
 * turns an int into binary with no trailing 0s
 * @param inputInt input number
 * @return string binary
 */
string intToBinary(int inputInt){
    string binary = bitset<32>(inputInt).to_string();
    bool hitAOne = false;
    string finaloutput = "";
    //this for loop removes any trailing 0s
    for(auto &l : binary){
        if(l != '0'){ //we wait till we hey a char that's a 1 before doing anything
            finaloutput += l;
            hitAOne = true;
        }else if(hitAOne){ // we accept all 1/0 after we hit the first 1
            finaloutput += l;
        }
    }
    return finaloutput;
}

/**
 * Reverses a string
 * @param stringIn string to be reversed
 * @return the reversed string
 */
string reverseString(string stringIn){
    string temp = stringIn;
    reverse(temp.begin(), temp.end()); //reverses string
    return temp;
}


#endif //MBASSEMBLER_SHAREDLIBRARY_HPP
