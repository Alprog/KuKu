#pragma once

#include <string>
#include "bytecode.h"
#include "localvar_info.h"
#include "opcode.h"
#include "cell.h"

namespace rt
{
    class function
    {
    public:
        std::string name;

        bytecode bytecode;
        std::vector<cell> constant_buffer;
        std::vector<localvar_info> locals;

        const localvar_info& get_local_info(int instruction_offset, int stack_offset) const;

        integer add_constant(cell cell);

        void full_dump();
        void print_instructions(bool include_comments);
        void print_constant_buffer();
        void print_locals_info();

        std::string get_comment(int index, base_instruction& instruction, std::string comment);
    };
}