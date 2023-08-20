#include "instruction.h"

#include <map>
#include <vector>

void Instruction::print() const {
    std::cout << "Destination Memory: " << m_destMem << std::endl;
    std::cout << "Is Memory Operation: " << (m_isMem ? "true" : "false") << std::endl;
    std::cout << "Immediate Value: " << m_imm << std::endl;
    std::cout << "Is Immediate Value: " << (m_isImm ? "true" : "false") << std::endl;
    std::cout << "Target: " << m_target << std::endl;
}

std::map<std::string, Register> Instruction::registerValues = {
        {"AYB", Register::AYB},
        {"BEN", Register::BEN},
        {"GIM", Register::GIM},
        {"DA", Register::DA},
        {"ECH", Register::ECH},
        {"ZA", Register::ZA},
        {"GH", Register::GH}
};

std::map<std::string, Opcode> Instruction::opcodeValues = {
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