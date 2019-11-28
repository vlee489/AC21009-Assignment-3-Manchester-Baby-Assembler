//
// Holds different configs used for the project
//

#ifndef MBASSEMBLER_CONFIG_HPP
#define MBASSEMBLER_CONFIG_HPP

#include <string>
#include <iostream>
using namespace std;

int numberOfInstructionsConfig = 7;
int numberOfMemoryLocationsConfig = 32;
int bitsNotUserAfterLineNo = 8;
int bitsNotUsedAfterFunctionNumber = 16;
int bitsUsedForLineNo = 5;
int bitsUsedForFunctionNo = 3;
int jumpFunctionNumber = 0;


void updateConfig(const string& txtConfig){
    ifstream reader(txtConfig);

    if (!reader) {
        cout << "Error opening config file" << endl;
        throw FILE_IO_ERROR;
    }

    string line;
    while (getline(reader, line)){ // read file line by line
        string option = "";
        string newVariable = "";
        bool optionFormed = false;
        //This for loop splits up each line into the option and the label
        for(auto &c : line){
            if(c == ';'){ //semicolons are used for comments so anything at and after the semicolon can be ignored
                break;
            }else if(c != ':' && !optionFormed){
                option += c;
            }else if(c == ':'){ // use use colon to split the option and the value
                optionFormed = true;
            }else{
                if(isdigit(c)){
                    newVariable += c;
                }
            }
        }
        if(!option.empty()){
            //Looks if the option exists and then assigns the new value if it does
            if(option == "numberOfInstructionsConfig"){
                numberOfInstructionsConfig = stoi(newVariable);
            }else if(option == "numberOfMemoryLocationsConfig"){
                numberOfMemoryLocationsConfig = stoi(newVariable);
            }else if(option == "bitsNotUserAfterLineNo"){
                bitsNotUserAfterLineNo = stoi(newVariable);
            }else if(option == "bitsNotUsedAfterFunctionNumber"){
                bitsNotUsedAfterFunctionNumber = stoi(newVariable);
            }else if(option == "bitsUsedForLineNo"){
                bitsUsedForLineNo = stoi(newVariable);
            }else if(option == "bitsUsedForFunctionNo"){
                bitsUsedForFunctionNo = stoi(newVariable);
            }else if(option == "jumpFunctionNumber"){
                jumpFunctionNumber = stoi(newVariable);
            }
        }
    }
    reader.close(); //close the config text file
}

#endif //MBASSEMBLER_CONFIG_HPP
