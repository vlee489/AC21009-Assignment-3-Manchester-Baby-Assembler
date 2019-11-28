# AC21009-Assignment-3-Manchester-Baby-Assembler
AC21009 Assignment 3 Manchester Baby Assembler

## Requirments
- GCC
- G++

## Building

### Build project
To build the project run the following command

   `make`

### Remove output files
To remove the output files that have occurred from previous builds, run the following command

   `make clean`

## Running / Usage

To use on UNIX use the follow command

`./assembler.o [Input-File*] [Output-File*] [Config-File] [Debug]`

***Any arguments with a \* are required***

### Input File
    This is your input text file with your assembly code.
    
### Output File
    This is the text file you want to output the Machine Code to.
    
### Config File
    This is the config file you want to use if you want a custom Config
    *See bellow for documentation*
    
### Debug
    Here you can use `-d` to enable to full debug dump.
    This dumps all debug into from all the Instruction and Variable containers as they run.
    
## Config File Usage
*See the included `configSample.txt` for an example.*

```
numberOfInstructionsConfig: 7
numberOfMemoryLocationsConfig: 32
bitsNotUserAfterLineNo: 8
bitsNotUsedAfterFunctionNumber: 16
bitsUsedForLineNo: 5
bitsUsedForFunctionNo: 3
mnemonics: [JMP JRP LDN STO SUB CMP STP]
functionNumbers: [0 1 2 3 4 6 7]
```

### Explanation of each config option accepting Ints

Each of these options should be named as following and then a **space** left 
before the the int value you want to use that option.

- **numberOfInstructionsConfig:** : This is the number of instruction your the computer you're assembling for should have and should match the number of item in the `mnemonics` and `functionNumbers`
- **numberOfMemoryLocationsConfig:** : This is the number of memory addresses your computer can use.
- **bitsNotUserAfterLineNo:** : This is the number of bits left blank after the Line Number.
- **bitsNotUsedAfterFunctionNumber:** : This is the number of bits left blank after the Function Number.
- **bitsUsedForLineNo:** : This is the number of bits used for the Line Number.
- **bitsUsedForFunctionNo:** : This is the number of bits used for the Function Number.

### Explanation of each config option accepting list

Each of these for their list should have square brackets `[` & `]` 
encapsulating each the list of items, as well no commas or speech marks 
should be used to surround each option.

- **mnemonics:** : Contains the mnemonics used in the assembly file.
- **functionNumbers** : Corresponding function number for the mnemonic.

For these 2 items you need to have each item in either list match up.

e.g. For the example above `JMP` will have the function number `0`. 
and then `SUB` would match up with the function number `4`.

## Error Codes
These are all the possible error codes and their meanings.

#### -101 : Value too big for the memory size
This error is when the the value passed through is too big to fit in the available memory size.

#### -102 : Out of Memory Range
When you look for a memory location that doesn't exist

#### -103 : Variable Name Present
When you've defined a variable already and you try to define it again

#### -104 : Variable Doesn't Exist
When you use a variable with an instruction that you haven't defined

#### -105 : Not Enough Memory
When there isn't enough memory locations to the number of Variables and Instructions.

#### -301 :  Instruction Doesn't Exist
Assembly used a Instruction that doesn't exist in the instruction Set

#### -302 : Vector Out of Range
When the assembler looks at an non-existent vector location 

#### -401 : Input too big
When the input int/long is too big

#### -501 : No Instruction to process
Assembler can't find instructions to process in the assembly file

#### -502 : Unable to find START or END markers
Can't find the `START` or/and `END` markers in the assembly file

#### -503 : Input Process Failed
Assembler failed to input you assembly file into it's data structure

#### -504 Invalid Input
invalid parameter given

#### -505 : File IO Error
There was an error opening your text file.

#### -506 : Variable used but not defined
When one of your instruction in your assembly file is used but not defined

#### -507 : Mis-Matched vectors
When you custom `mnemonics` and `functionNumbers` in your config text file 
don't have the same number of items in each to match up.

#### -508 : Line number too large for bits defined
When the line number of a variable is too large for the number of bits 
defined to hold the bits in machine code.

#### -509 : Function Number too large for bits defined
When the function number of a variable is too large for the number of bits 
defined to hold the bits in machine code.

### -510 : Invalid char in config file
When there's a invalid char in the config file,
e.g when you have a non decimal number when defining the function numbers

#### -511 : Mis-matched config details
When parts of config don't match, 
mainly numberOfInstructionsConfig and the number of mnemonics stated


