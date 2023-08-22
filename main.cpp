#include "cpu.h"

int main () {
    CPU cpu;
    std::string filename = "instructions.txt";
    cpu.parse(filename);

//    cpu.printReg();
//    cpu.printInstruction();
//    cpu.dumpMemory();
}
