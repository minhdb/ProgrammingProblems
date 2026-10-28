// #define _DEBUG

#include <unordered_map>
#include <vector>
#include <limits>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstdint>

using OpCodeTable = std::unordered_map<std::string, std::pair<uint8_t, bool>>;

const OpCodeTable kOpCodes {
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

struct IOStream
{
    void IgnoreLineIn() const
    {
        vm_in.clear();
        vm_in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::istream& vm_in;
    std::ostream& vm_out;
    std::ostream& vm_err;
};

struct VMConfig
{
    VMConfig()
        : memory_size_(0)
        , begin_offset_(0)
        , num_elements_(0)
        , num_elements_per_line_(0)
        , bytes_per_element_(1)
    {}
    VMConfig(const VMConfig&) = default;
    VMConfig& operator=(const VMConfig&) = default;
    ~VMConfig() = default;

    uint64_t memory_size_;
    uint64_t begin_offset_;
    uint64_t num_elements_;
    uint64_t num_elements_per_line_;
    uint64_t bytes_per_element_;
};

class CoolVirtualMachine
{
public:
    CoolVirtualMachine() = delete;
    CoolVirtualMachine(VMConfig& config)
        : vm_config_(config)
        , mem_(config.memory_size_, 0)
    {}

    CoolVirtualMachine(const CoolVirtualMachine&) = delete;
    CoolVirtualMachine& operator=(const CoolVirtualMachine&) = delete;
    ~CoolVirtualMachine() = default;

    /*
     * Dump the memory in hex of in mem_ to the output device.
     */
    void PrintMemory(const IOStream& io_stream) const
    {
        io_stream.vm_out << "Total memory: " << vm_config_.memory_size_;
        // Potential overflow here. How to deal with it?
        uint64_t end_addr = vm_config_.begin_offset_ +
            vm_config_.num_elements_ * vm_config_.bytes_per_element_;
        uint64_t count_element = 0;

        // Also want to do bound checking here. end_addr might go pass
        // mem_ total size. Solved by only print within the total memory
        // size.
        end_addr = end_addr < vm_config_.memory_size_ ?
            end_addr : vm_config_.memory_size_;

        for (uint64_t start_addr = vm_config_.begin_offset_; start_addr < end_addr;
            start_addr += vm_config_.bytes_per_element_) {
                if (count_element == vm_config_.num_elements_per_line_) {
                    io_stream.vm_out << "\n";
                    count_element = 0;
                }

                // Print each element.
                for (uint8_t i = 0; i < vm_config_.bytes_per_element_; i++) {
                    io_stream.vm_out << std::setfill('0') << std::setw(2);
                    io_stream.vm_out << std::hex << (0xFF & mem_[start_addr + i]);
                    // printf("%02hhx", mem_[start_addr + i]);
                }

                count_element++;
                io_stream.vm_out << " ";
            }
        io_stream.vm_out << "\n";
    }

    /*
     * Get ASM instructions.
     */
    void GetInstructions(const IOStream& io_stream)
    {
        std::string asm_instruction;
        uint64_t start_addr = 0;

        // TODO: Handle invalid input.
        while (std::getline(io_stream.vm_in, asm_instruction)) {
            #ifdef _DEBUG
            std::cout << asm_instruction << std::endl;
            #endif
            // Read the instructions into memory.
            // Need a better way to do this, what happens if the opcode's length
            // is no longer 3?
            std::string op_code = asm_instruction.substr(0, 3);
            if (kOpCodes.find(op_code) != kOpCodes.end()) {
                uint64_t op_code_encoded = (kOpCodes.at(op_code).first) << 0x2;

                uint8_t width_char = asm_instruction[3] - '0';
                uint64_t width = 0;

                switch (width_char) {
                    case 2: width = 1; break;
                    case 4: width = 2; break;
                    case 8: width = 3; break;
                }

                // uint8_t width_char_copy = width_char;
                // while (width_char_copy >>= 1) width++;

                op_code_encoded |= width;

                // Write opcode and the width to the first byte.
                mem_[start_addr] = op_code_encoded;

                // Check if there's a parameter. If there's a parameter, write it
                // to memory according to the width.
                if (kOpCodes.at(op_code).second) {
                    // Same problem with the opcode's length. If the opcode's length
                    // is not 3, this needs to be changed.
                    std::string param = asm_instruction.substr(5);

                    // This could fail.
                    // "You can assume that none of the tests cases will overflow operands or results"
                    int64_t param_int = std::stol(param);

                    for (int i = width_char; i > 0; i--) {
                        mem_[start_addr + i] = param_int & 0xFF;
                        param_int >>= 8U;
                    }

                    start_addr += width_char;
                }

                start_addr += 1;
            }
        }
    }

    /*
     * Big Endian system: stores the MSB at the smallest
     *     address and the LSB at the largest.
     *
     * Assumption: Some of the test cases could overflow operands or results.
     *
     * There are two possible solutions:
     * 1. Truncate the result into [width] least significant bytes and place it
     * into memory. This is the current solution. It doesn't solve the problem.
     *
     * 2. Let the operands overflow into memory. Dangerous and harder to deal
     * with since we don't know how many bytes the result/operand overflow
     * into. Plus, the operands could be larger than a 64-bit signed long long
     * integer can represent.
     *
     * So I decided to stick with the first solution instead.
     *
     * Sure, we can extract a byte one by one and grow the stack pointer.
     *
     * How to know when overflow happens?
     * When we shift right param by [width] bytes and param is still not zero.
     * We might be able to accomodate this by breaking the result into two
     * segments of 8 bytes with a total of 16 bytes to store the result.
     *
     * If overflow happens, push the rest of the last 8 bytes onto the stack.
     *
     * Example:
     * psh8 9999999999999999
     * psh8 9999999999999999
     * mlt8 2
     *
     * // The stack should be empty here. But it's not going to be empty after
     * // an overflowed operation.
     * pop8
     * hlt2
     *
     * What to do with invalid instructions? Such as popping from the stack when
     * there's nothing on the stack?
     */
    void ExecuteASM(const IOStream& io_stream)
    {
        uint64_t pc = 0;
        uint64_t sp = vm_config_.memory_size_ - 1;

        // Problem: What happens when the pc go pass sp?
        // Or when the stack overflow into the instructions?
        // Problem count_instr might cause problem on certain programs with jmp
        // instruciton.
        while (pc < vm_config_.memory_size_) {
            // Read the first byte for op_code.
            uint64_t op_code = mem_[pc] >> 2U;

            // Read the width.
            // 01 (1) means width = 2
            // 10 (2) means width = 4
            // 11 (3) means width = 8
            uint64_t width = 1U << (mem_[pc] & 3U);

            // Read the param.
            int64_t param = 0;
            for (uint8_t i = 1; i <= width; i++) {
                param |= mem_[pc + i];
                if (i != width)
                    param <<= 8U;
            }

            // Realign param due to the extra shift left at the end of the loop.
            // param >>= 8U;

            #ifdef _DEBUG
            std::cout << op_code << " " << width << " " << param << std::endl;
            #endif

            int64_t first_val = 0;
            int64_t second_val = 0;
            int64_t sum = 0;
            int64_t prod = 1;

            bool all_less = true;
            bool all_equal = true;

            switch (op_code) {
                case 1:
                    // hlt: causes the machine to stop processing. No param.
                    pc += 1;
                    return;
                case 2:
                    // psh: Push the parameter to the stack and increase sp. Has param.
                    PushHelper(sp, param, width);
                    pc += (1 + width);
                    break;
                case 3:
                    // pop: Pop from the top of the stack and decreases the sp. No param.
                    // Problem: when sp == memory_size_ - 1;
                    PopHelper(sp, width);
                    pc += 1;
                    break;
                case 4:
                    // equ: Pops "parameter count" values (v1, v2, .., vcount) from
                    // the stack. If v1==v2==..==vcount, pushes 1 back, otherwise pushes
                    // 0 back. Has param.
                    second_val = PopHelper(sp, width);
                    param--;

                    while (param--) {
                        first_val = PopHelper(sp, width);

                        if (second_val != first_val) {
                            all_equal = false;
                        }
                    }

                    if (all_equal) {
                        PushHelper(sp, 1, width);
                    } else {
                        PushHelper(sp, 0, width);
                    }

                    pc += (1 + width);
                    break;
                case 5:
                    // lth: Pops" parameter count" values (v1, v2,..., vcount) from
                    // the stack. If v1 < v2 < .. < vcount, pushes 1 back, otherwise
                    // pushes 0 back. Has param.
                    second_val = PopHelper(sp, width);
                    param--;

                    while (param--) {
                        first_val = PopHelper(sp, width);

                        if (second_val >= first_val) {
                            all_less = false;
                        }
                    }

                    if (all_less) {
                        PushHelper(sp, 1, width);
                    } else {
                        PushHelper(sp, 0, width);
                    }

                    pc += (1 + width);
                    break;
                case 6:
                    // inc: Pops a value from the stack, increments it, and pushes
                    // the resulting value back. No param.
                    first_val = PopHelper(sp, width);
                    PushHelper(sp, first_val + 1, width);

                    pc += 1;
                    break;
                case 7:
                    // adds: Pops (v1, v2, ..., vcount) from the stack, performs
                    // v1 + v2 + .. + vcount = Z and pushes Z back to the stack. Has param.
                    sum = PopHelper(sp, width);
                    // printf("%ld\n", sum);
                    param--;
                    while (param--) {
                        sum += PopHelper(sp, width);
                    }

                    // printf("%ld\n", sum);
                    // Need to build a mask here?
                    PushHelper(sp, sum, width);

                    pc += (1 + width);
                    break;
                case 8:
                    // mlt: Pops (v1, v2, ..., vcount) from the stack, performs
                    // v1 * v2 ... * vcount = Z and pushes Z back to the stack.
                    // Has param.
                    prod = PopHelper(sp, width);
                    param--;
                    while (param--) {
                        prod *= PopHelper(sp, width);
                    }

                    // Need to build a mask here?
                    PushHelper(sp, prod, width);
                    pc += (1 + width);
                    break;
                case 9:
                    // jmp: Adjusts the program counter by the parameter as an offset
                    // to the current program counter. Note this is applied after moving
                    // the pc past the current instruction. Has param.
                    pc += (param + 1 + width);
                    break;
                case 10:
                    // jmf: Pops a value off the stack. If the value is zero,
                    // moves the pc like a jmp instruction, otherwise no action is performed.
                    // Has param.
                    first_val = PopHelper(sp, width);
                    if (first_val == 0)
                        pc += (param + width + 1);
                    else
                        pc += (1 + width);
                    break;
                default:
                    break;
            }
        }
    }

private:
    int64_t PopHelper(uint64_t& sp, uint64_t width)
    {
        int64_t pop_val = 0;
        for (uint64_t i = 1; i <= width; i++) {
            pop_val |= mem_[sp + i];
            if (i != width)
                pop_val <<= 8U;
            // Don't need to zero out the memory.
            // mem_[sp + i] &= 0;
        }
        // pop_val >>= 8U;
        sp += width;

        return pop_val;
    }

    void PushHelper(uint64_t& sp, int64_t param, uint64_t width)
    {
        for (uint64_t i = 0; i < width; i++) {
            // Extract 1 byte one-by-one.
            mem_[sp-i] = (param >> (i * 8U)) & 0xFF;
        }

        sp -= width;
    }

    VMConfig vm_config_;

    std::vector<uint8_t> mem_;
};

void ReadConfiguration(const IOStream& io_stream, VMConfig& config)
{
    // TODO: Change something about this lazy approach.
    // 31U is 11111 in binary. Everytime an input is valid, turn on the bit for
    // valid_flag.
    const uint8_t kValidInput = 0b11111;
    uint8_t valid_flag = 0U;

    // Overall:
    // begin_offset_ + num_elements_ * bytes_per_element_ < memory_size_;
    // If not, prompt the user to input again.
    while (valid_flag != kValidInput) {
        // Possible scenarios of invalid input
        // 1. User input a too large/too small number.
        // 2. User input a valid number but the OS does not permit such allocation
        // size for a single buffer.
        // 3. User input some non-integer characters.
        io_stream.vm_in >> config.memory_size_;
        if (io_stream.vm_in.fail()) {
            io_stream.IgnoreLineIn();
            io_stream.vm_err << "Invalid memory size.\n";
            valid_flag = 0U;
            continue;
        } else {
            // Allocation might fail even with valid input.
            valid_flag |= 1;
        }

        // Possible invalid input.
        // 1. User input a number which is outside of the range of [0, memory_size_]
        // 2. User input some non-integer characters.
        io_stream.vm_in >> config.begin_offset_;
        if (io_stream.vm_in.fail() || config.begin_offset_ >= config.memory_size_) {
            io_stream.IgnoreLineIn();
            io_stream.vm_err << "Invalid begin offset.\n";
            valid_flag = 0U;
            continue;
        } else {
            valid_flag |= (1U << 1);
        }

        // Possible invalid input.
        // User input anything rather than 1, 2, 4, or 8.
        io_stream.vm_in >> config.bytes_per_element_;
        if (io_stream.vm_in.fail()) {
            io_stream.IgnoreLineIn();
            valid_flag = 0U;
            continue;
        } else {
            switch (config.bytes_per_element_) {
                case 1:
                case 2:
                case 4:
                case 8:
                    valid_flag |= (1U << 2);
                    break;
                default:
                    io_stream.IgnoreLineIn();
                    io_stream.vm_err << "Invalid bytes per element. Either 1, 2, 4, or 8.\n";
                    valid_flag = 0U;
                    continue;
            }
        }

        io_stream.vm_in >> config.num_elements_;
        if (io_stream.vm_in.fail()) {
            io_stream.IgnoreLineIn();
            io_stream.vm_err << "Invalid number of elements to print out.\n";
            valid_flag = 0U;
        } else {
            valid_flag |= (1U << 3);
        }

        io_stream.vm_in >> config.num_elements_per_line_;
        if (io_stream.vm_in.fail()) {
            io_stream.IgnoreLineIn();
            io_stream.vm_err << "Invalid number of elements per line.\n";
            valid_flag = 0U;
        } else {
            valid_flag |= (1U << 4);
        }

        #ifdef _DEBUG
            std::cout << config.memory_size_ << " " << config.begin_offset_
                << " " << config.bytes_per_element_ << " " << config.num_elements_
                << " " << config.num_elements_per_line_ << "\n";
        #endif
    }
}

int main() {
    IOStream io_stream {std::cin, std::cout, std::cerr};

    VMConfig new_vm_config;

    ReadConfiguration(io_stream, new_vm_config);
    CoolVirtualMachine coolVM1(new_vm_config);

    coolVM1.GetInstructions(io_stream);
    coolVM1.ExecuteASM(io_stream);
    coolVM1.PrintMemory(io_stream);
    return 0;
}
