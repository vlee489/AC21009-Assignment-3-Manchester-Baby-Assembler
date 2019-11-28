#include <iostream>
#include "variable.hpp"
#include "error.hpp"
#include "variableList.hpp"
#include "instruction.hpp"
#include "sharedLibrary.hpp"
#include "instructionList.hpp"
#include "assemblerFunctions.hpp"

int main(){
    cout << "end" << endl;
    string hi =  toBinary(123);
    cout << reverseString(hi) << endl;
}