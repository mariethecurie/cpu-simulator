#ifndef CPU_H
#define CPU_H

#include "instruction.h"
#include <map>
#include <vector>
#include <iostream>

class CPU {
public:
    CPU ();

    void parse (const std::string& filename);
    void execute ();

    void MOV (const Instruction& i);
    void ADD (const Instruction& i);
    void SUB (const Instruction& i);
    void MUL (const Instruction& i);
    void DIV (const Instruction& i);
    void AND (const Instruction& i);
    void OR (const Instruction& i);
    void NOT (const Instruction& i);
    void CMP (const Instruction& i);
    
    void dumpMemory ();
//    void printInst ();
//    void printReg ();

private:
    std::map<std::string, int> labels;
    std::map<int, std::vector<std::string>> instructions;
    std::vector<Instruction> parsedInstructions;
    std::map<Register, int> registers;
    std::map<Opcode, void(CPU::*)(const Instruction&)> ALU;
    std::vector<int> memory;
};

#endif
