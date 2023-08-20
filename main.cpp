#include "cpu.cpp"

int main () {
    CPU cpu;
    std::string filename = "instructions.txt";
    cpu.parse(filename);
    cpu.printInstruction();
    cpu.dumpMemory();
}