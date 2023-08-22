#include "instruction.h"

Instruction::Instruction () {
    registerValues = {
            {"AYB", Register::AYB},
            {"BEN", Register::BEN},
            {"GIM", Register::GIM},
            {"DA", Register::DA},
            {"ECH", Register::ECH},
            {"ZA", Register::ZA},
            {"GH", Register::GH}
    };
    opcodeValues = {
            {"MOV", Opcode::MOV},
            {"ADD", Opcode::ADD},
            {"SUB", Opcode::SUB},
            {"MUL", Opcode::MUL},
            {"DIV", Opcode::DIV},
            {"AND", Opcode::AND},
            {"OR", Opcode::OR},
            {"NOT", Opcode::NOT},
            {"CMP", Opcode::CMP},
            {"JMP", Opcode::JMP},
            {"JG", Opcode::JG},
            {"JL", Opcode::JL},
            {"JE", Opcode::JE}
    };
}
void Instruction::setOpcode (const std::string& opcode) {
    m_opcode = opcodeValues[opcode];
}
Opcode Instruction::opcode () const {
    return m_opcode;
}
void Instruction::setDestReg (const std::string& destReg) {
    m_destReg = registerValues[destReg];
}
Register Instruction::destReg () const {
    return m_destReg;
}
void Instruction::setDestMem (int destMem) {
    m_destMem = destMem;
    m_isMem = true;
}
int Instruction::destMem () const {
    return m_destMem;
}
bool Instruction::isMem () const {
    return m_isMem;
}
void Instruction::setSrcReg (const std::string& srcReg) {
    m_srcReg = registerValues[srcReg];
}
Register Instruction::srcReg () const {
    return m_srcReg;
}
void Instruction::setImm (int imm) {
    m_imm = imm;
    m_isImm = true;
}
int Instruction::imm () const {
    return m_imm;
}
bool Instruction::isImm () const {
    return m_isImm;
}
void Instruction::setTarget (int target) {
    m_target = target;
}
int Instruction::target () const {
    return m_target;
}
