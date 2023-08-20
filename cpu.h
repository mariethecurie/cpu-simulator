#ifndef CPU_H
#define CPU_H

#include <map>
#include <vector>

class CPU {
public:
    CPU ();
    ~CPU () {}

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

    void printInstruction();
    void dumpMemory ();

private:
    std::map<std::string, int> labels;
    std::map<int, std::vector<std::string>> instructions;
    std::vector<Instruction> parsedInstructions;
    std::map <Register, int8_t> registers;
    std::map<Opcode, void(CPU::*)(const Instruction&)> ALU;
    std::vector<int8_t> memory;
};

#endif