#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <map>

enum class Register {
    AYB,
    BEN,
    GIM,
    DA,
    ECH,
    ZA,
    GH
};

enum class Opcode {
    MOV,
    ADD,
    SUB,
    MUL,
    DIV,
    AND,
    OR,
    NOT,
    CMP,
    JMP,
    JG,
    JL,
    JE
};

class Instruction {
public:
    Instruction ();
    void setOpcode (const std::string& opcode);
    Opcode opcode () const;
    void setDestReg (const std::string& destReg);
    Register destReg () const;
    void setDestMem (int destMem);
    int destMem () const;
    bool isMem () const;
    void setSrcReg (const std::string& srcReg);
    Register srcReg () const;
    void setImm (int imm);
    int imm () const;
    bool isImm () const;
    void setTarget (int target);
    int target () const;

private:
    Opcode m_opcode;
    Register m_destReg;
    Register m_srcReg;
    int m_destMem;
    bool m_isMem;
    int m_imm;
    bool m_isImm = false;
    int m_target;
    std::map<std::string, Opcode> opcodeValues;
    std::map<std::string, Register> registerValues;
};

#endif
