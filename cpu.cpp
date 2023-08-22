#include "cpu.h"

#include <fstream>
#include <sstream>

CPU::CPU () {
    // Initializing the ALU map with function pointers
    ALU[Opcode::MOV] = &CPU::MOV;
    ALU[Opcode::ADD] = &CPU::ADD;
    ALU[Opcode::SUB] = &CPU::SUB;
    ALU[Opcode::MUL] = &CPU::MUL;
    ALU[Opcode::DIV] = &CPU::DIV;
    ALU[Opcode::AND] = &CPU::AND;
    ALU[Opcode::OR] = &CPU::OR;
    ALU[Opcode::NOT] = &CPU::NOT;
    ALU[Opcode::CMP] = &CPU::CMP;

    // Initializing registers and memory
    registers[Register::AYB] = 0;
    registers[Register::BEN] = 0;
    registers[Register::GIM] = 0;
    registers[Register::DA] = 0;
    registers[Register::ECH] = 0;
    registers[Register::ZA] = 0;
    registers[Register::GH] = 0;

    memory.resize(32);
}

void CPU::parse (const std::string& filename) {
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
    }

    std::string instructionLine;
    int instructionIndex = -1;
    while (std::getline(inputFile, instructionLine)) {
        ++instructionIndex;
        if (instructionLine.back() == ':') {
            instructionLine.pop_back();
            labels[instructionLine] = instructionIndex;
            --instructionIndex;
        } else {
            std::istringstream iss(instructionLine);
            std::string splittedPart;
            std::vector<std::string> splittedInstruction;

            while (iss >> splittedPart) {
                splittedInstruction.push_back(splittedPart);
            }
            instructions[instructionIndex] = splittedInstruction;
        }
    }

    for (const auto& pair : instructions) {
        Instruction instruction;
        std::vector<std::string> inst = pair.second;
        inst[1].erase(inst[1].size() - 1);
        instruction.setOpcode(inst[0]);
        // Checking if the opcode is jump operation, so that the label will be replaced by the address
        if (instruction.opcode() == Opcode::JMP || instruction.opcode() == Opcode::JG
        || instruction.opcode() == Opcode::JL || instruction.opcode() == Opcode::JE) {
            instruction.setTarget(labels[inst[1]]);
        }
        // Checking if the destination operand is memory address or register
        if (inst[1][0] == '[') {
            instruction.setDestMem(inst[1][1] - '0');
        } else {
            instruction.setDestReg(inst[1]);
        }

        if (inst.size() == 3) {
            // Checking if the source operand is immediate or register
            if (isdigit(inst[2][0])) {
                instruction.setImm(std::stoi(inst[2]));
            } else {
                instruction.setSrcReg(inst[2]);
            }
        }

        parsedInstructions.push_back(instruction);
    }

    execute();

    inputFile.close();
}

void CPU::execute () {

    registers[Register::GH] = 0;

    while (registers[Register::GH] < parsedInstructions.size()) {
        Instruction currentInstruction = parsedInstructions[registers[Register::GH]];
        if (currentInstruction.opcode() == Opcode::JMP) {
            registers[Register::GH] = currentInstruction.target();
            continue;
        } else if (currentInstruction.opcode() == Opcode::JG) {
            if (registers[Register::DA] == 1) {
                registers[Register::GH] = currentInstruction.target();
                continue;
            }
        } else if (currentInstruction.opcode() == Opcode::JL) {
            if (registers[Register::DA] == -1) {
                registers[Register::GH] = currentInstruction.target();
                continue;
            }
        } else if (currentInstruction.opcode() == Opcode::JE) {
            if (registers[Register::DA] == 0) {
                registers[Register::GH] = currentInstruction.target();
                continue;
            }
        }

        (this->*ALU[currentInstruction.opcode()])(currentInstruction);
        ++registers[Register::GH];
    }
}

// ALU operations
void CPU::MOV (const Instruction& i) {
    if (i.isMem()) {
        if (i.isImm()){
            memory[i.destMem()] = i.imm();
        } else {
            memory[i.destMem()] = registers[i.srcReg()];
        }
    } else if (i.isImm()) {
        registers[i.destReg()] = i.imm();
    } else {
        registers[i.destReg()] = registers[i.srcReg()];
    }
}
void CPU::ADD (const Instruction& i) {
    if (i.isMem()) {
        if (i.isImm()){
            memory[i.destMem()] += i.imm();
        } else {
            memory[i.destMem()] += registers[i.srcReg()];
        }
    } else if (i.isImm()) {
        registers[i.destReg()] += i.imm();
    } else {
        registers[i.destReg()] += registers[i.srcReg()];
    }
}
void CPU::SUB (const Instruction& i) {
    if (i.isMem()) {
        if (i.isImm()){
            memory[i.destMem()] -= i.imm();
        } else {
            memory[i.destMem()] -= registers[i.srcReg()];
        }
    } else if (i.isImm()) {
        registers[i.destReg()] -= i.imm();
    } else {
        registers[i.destReg()] -= registers[i.srcReg()];
    }
}
void CPU::MUL (const Instruction& i) {
    if (i.isMem()) {
        registers[Register::AYB] *= memory[i.destMem()];
    }
    registers[Register::AYB] *= registers[i.destReg()];
}
void CPU::DIV (const Instruction& i) {
    if (i.isMem()) {
        registers[Register::DA] = registers[Register::AYB] % memory[i.destMem()];
        registers[Register::AYB] /= memory[i.destMem()];
    }
    registers[Register::DA] = registers[Register::DA] % registers[i.destReg()];
    registers[Register::AYB] /= registers[i.destReg()];
}
void CPU::AND (const Instruction& i) {
    if (i.isMem()) {
        if (i.isImm()){
            memory[i.destMem()] &= i.imm();
        } else {
            memory[i.destMem()] &= registers[i.srcReg()];
        }
    } else if (i.isImm()) {
        registers[i.destReg()] &= i.imm();
    } else {
        registers[i.destReg()] &= registers[i.srcReg()];
    }
}
void CPU::OR (const Instruction& i) {
    if (i.isMem()) {
        if (i.isImm()){
            memory[i.destMem()] |= i.imm();
        } else {
            memory[i.destMem()] |= registers[i.srcReg()];
        }
    } else if (i.isImm()) {
        registers[i.destReg()] |= i.imm();
    } else {
        registers[i.destReg()] |= registers[i.srcReg()];
    }
}
void CPU::NOT (const Instruction& i) {
    if (i.isMem()) {
        memory[i.destMem()] = ~memory[i.destMem()];
    }
    registers[i.destReg()] = ~registers[i.destReg()];
}
void CPU::CMP (const Instruction& i) {
    int result;
    if (i.isMem()) {
        if (i.isImm()){
            result = memory[i.destMem()] - i.imm();
        } else {
            result = memory[i.destMem()] - registers[i.srcReg()];
        }
    } else if (i.isImm()) {
        result = registers[i.destReg()] - i.imm();
    } else {
        result = registers[i.destReg()] - registers[i.srcReg()];
    }

    if (result == 0) {
        registers[Register::DA] = 0;
    } else if (result > 0) {
        registers[Register::DA] = 1;
    } else {
        registers[Register::DA] = -1;
    }
}

void CPU::dumpMemory () {
   for (int i = 0; i < memory.size(); ++i) {
       std::cout << i << ": " << memory[i] << std::endl;
   }
}
//void CPU::printInstruction() {
//   for (const auto& pair : instructions) {
//       std::cout << "Instruction Index: " << pair.first << std::endl;
//       const std::vector<std::string>& parts = pair.second;
//       for (const std::string& part : parts) {
//           std::cout << "  " << part << std::endl;
//       }
//   }
//}
//void CPU::printReg () {
//    std::cout << "Registers:" << std::endl;
//    for (const auto& pair : registers) {
//        std::cout << "Key: " << static_cast<int>(pair.first) << ", Value: " << pair.second << std::endl;
//    }
//}
