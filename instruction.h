#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <iostream>
#include <string>
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
    Instruction () {}
    ~Instruction() {}
    void setOpcode (const std::string& opcode) {
        m_opcode = opcodeValues[opcode];
    }
    Opcode opcode () const {
        return m_opcode;
    }
    void setDestReg (const std::string& destReg) {
        m_destReg = registerValues[destReg];
    }
    Register destReg () const {
        return m_destReg;
    }
    void setDestMem (int destMem) {
        m_destMem = destMem;
        m_isMem = true;
    }
    int destMem () const {
        return m_destMem;
    }
    bool isMem () const {
        return m_isMem;
    }
    void setSrcReg (const std::string& srcReg) {
        m_srcReg = registerValues[srcReg];
    }
    Register srcReg () const {
        return m_srcReg;
    }
    void setImm (int imm) {
        m_imm = imm;
        m_isImm = true;
    }
    int imm () const {
        return m_imm;
    }
    bool isImm () const {
        return m_isImm;
    }
    void setTarget (int target) {
        m_target = target;
    }
    int target () const {
        return m_target;
    }
    void print() const;

private:
    Opcode m_opcode;
    Register m_destReg;
    Register m_srcReg;
    int m_destMem;
    bool m_isMem;
    int m_imm;
    bool m_isImm;
    int m_target;
    static std::map<std::string, Opcode> opcodeValues;
    static std::map<std::string, Register> registerValues;
};

#endif