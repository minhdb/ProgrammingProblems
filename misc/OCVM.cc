/**
 * OC interview question.
 *
 * Write a VM that simulates a computer.
 */

#include <unordered_map>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <utility>
#include <cassert>

using std::unordered_map;
using std::string;
using std::pair;

const unordered_map<string, pair<int, bool>> kOpCodes{
    {"hlt", {1, false}},
    {"psh", {2, true}},
    {"pop", {3, false}},
    {"equ", {4, true}},
    {"lth", {5, true}},
    {"inc", {6, false}},
    {"add", {7, true}},
    {"mlt", {8, true}},
    {"jmp", {9, true}},
    {"jmf", {10, true}}
};

class CoolAssembler
{
public:
    CoolAssembler() = delete;

    CoolAssembler(unsigned long memorySizeInBytes, unsigned long printBeginOffset,
            unsigned short bytesPerElement, unsigned long numElementsToPrint,
            unsigned long numElementsPerLine)
        : memory_size_(memorySizeInBytes)
        , begin_offset_(printBeginOffset)
        , bytes_per_element_(bytesPerElement)
        , num_elements_(numElementsToPrint)
        , num_elements_per_line_(numElementsPerLine)
        , mem_(new unsigned char[memory_size_])
    {

    }

    CoolAssembler(const CoolAssembler&) = delete;
    CoolAssembler& operator=(const CoolAssembler&) = delete;

    ~CoolAssembler()
    {
        if (mem_ != nullptr)
            delete[] mem_;
    }

    void PrintMemory()
    {
        // Potential overflow here.
        unsigned long end_addr = begin_offset_ + num_elements_ * bytes_per_element_;
        unsigned long count_element = 0;

        // Also want to do bound checking here. Invalid input? end_addr might go pass
        // mem_ total size.
        //
        // Bound checking
        end_addr = end_addr < memory_size_ ? end_addr : memory_size_;
        for (unsigned long start_addr = begin_offset_; start_addr < end_addr; 
                start_addr += bytes_per_element_) {
            if (count_element == num_elements_per_line_) {
                printf("\n");
                count_element = 0;
            }

            // Print each element.
            for (unsigned short i = 0; i < bytes_per_element_; i++) {
                printf("%02hhx", mem_[start_addr + i]);
            }

            count_element++;
            printf(" ");
        }
    }

    void GetInstructions()
    {
        // Get ASM instructions.
        string asm_instruction;
        unsigned long start_addr = 0;
        while (std::getline(std::cin, asm_instruction)) {

            // Read the instruction into memory.
            string op_code = asm_instruction.substr(0, 3);
            if (kOpCodes.find(op_code) != kOpCodes.end()) {
                unsigned long op_code_encoded = (kOpCodes.at(op_code).first) << 0x2;

                unsigned short width_char = asm_instruction[3] - '0';
                unsigned long width = 0;

                
                switch (width_char) {
                    case 2:
                        width = 0x1;
                        break;
                    case 4:
                        width = 0x2;
                        break;
                    case 8:
                        width = 0x3;
                }
                

                // If width_char = 2, then width = 1.
                // If width_char = 4, then width = 2.
                // If width_char = 8, then width = 3.
                //unsigned width_char_copy = width_char;
                //while (width_char_copy >>= 1) width++;

                op_code_encoded |= width;

                // Write opcode and the width to the first byte.
                mem_[start_addr] = op_code_encoded;

                // Check if there's a param. If there's a param, write it to memory
                // according to the width.
                if (kOpCodes.at(op_code).second) {
                    string param = asm_instruction.substr(5);
                    long param_int = std::stol(param);

                    for (unsigned i = width_char; i > 0; i--) {
                        mem_[start_addr + i] = param_int & 0xFF;
                        param_int >>= 0x8;
                    }

                    start_addr += width_char;
                }

                start_addr += 1;
            }       
        }
    }

private:
    // Memory size in bytes.
    unsigned long memory_size_;

    // Offset address to print out.
    unsigned long begin_offset_;

    // Number of bytes per element.
    unsigned short bytes_per_element_;

    // Number of elements.
    unsigned long num_elements_;

    // Number of elements per line.
    unsigned long num_elements_per_line_;
    unsigned char* mem_;
};


void PrintMemory(unsigned char mem[], unsigned long memorySizeInBytes,
        unsigned long printBeginOffset, unsigned short bytesPerElement,
        unsigned long numElementsToPrint, unsigned long numElementsPerLine)
{
    unsigned long end_addr = printBeginOffset + numElementsToPrint * bytesPerElement;
    end_addr = end_addr < memorySizeInBytes ? end_addr : memorySizeInBytes;
    unsigned long countElement = 0;

    for (size_t start_addr = printBeginOffset; start_addr < end_addr; start_addr += bytesPerElement) {
        if (countElement == numElementsPerLine) {
            printf("\n");
            countElement = 0;
        }

        // Print each element.
        for (size_t i = 0; i < bytesPerElement; i++) {
            printf("%02hhx", mem[start_addr + i]);
        }

        countElement++;
        printf(" ");
    }
    printf("\n");
}

void GetASMInstructions(unsigned char mem[])
{
    // Get ASM instructions.
    string asm_instruction;
    unsigned long start_addr = 0;
    while (std::getline(std::cin, asm_instruction)) {
        // Read the instruction into memory.
        string op_code = asm_instruction.substr(0, 3);
        if (kOpCodes.find(op_code) != kOpCodes.end()) {
            unsigned long op_code_encoded = (kOpCodes.at(op_code).first) << 0x2;

            unsigned short width_char = asm_instruction[3] - '0';
            unsigned long width = 0;
            switch (width_char) {
                case 2:
                    width = 0x1;
                    break;
                case 4:
                    width = 0x2;
                    break;
                case 8:
                    width = 0x3;
            }

            unsigned char width_test = 0;
            while (width_char >>= 1) width_test++;
            assert(width_test == width);

            op_code_encoded |= width;

            // Write opcode and the width to the first byte.
            mem[start_addr] = op_code_encoded;

            // CHeck if there's a param. If there's a param, write it to memory
            // according to the width.
            if (kOpCodes.at(op_code).second) {
                string param = asm_instruction.substr(5);
                long param_int = std::stol(param);

                for (unsigned i = width_char; i > 0; i--) {
                    mem[start_addr + i] = param_int & 0xFF;
                    param_int >>= 0x8;
                }

                start_addr += width_char;
            }

            start_addr += 1;
        }    
    }
}

int main()
{
    unsigned long memorySizeInBytes = 0;
    unsigned long printBeginOffset = 0;
    unsigned short bytesPerElement = 1;
    unsigned long numElementsToPrint = 0;
    unsigned long numElementsPerLine = 0;

    // Get memory config.
    scanf("%lu %lu %hu %lu %lu", &memorySizeInBytes, &printBeginOffset,
            &bytesPerElement, &numElementsToPrint, &numElementsPerLine);

    unsigned char mem[memorySizeInBytes];
    memset(mem, 0, memorySizeInBytes);
    PrintMemory(mem, memorySizeInBytes, printBeginOffset, bytesPerElement, 
            numElementsToPrint, numElementsPerLine);
    GetASMInstructions(mem);
    PrintMemory(mem, memorySizeInBytes, printBeginOffset, bytesPerElement, 
            numElementsToPrint, numElementsPerLine);


    return 0;
}
