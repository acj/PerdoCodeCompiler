/*
 *   Assembler.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <iostream>
#include <vector>
#include <string>
#include <time.h>
using namespace std;


class Assembler
{
    public:
        Assembler(string);
        inline void add_int_code(string command) 
        { commands.push_back(command); }

        void output_intermediate();
        void translate();

    private:
        struct perdo_register
        {
            int     mem_pos;    // Memory cell currently in this register
            int     time;       // Unitless time when last populated
        };
        typedef struct perdo_register perdo_register;

        struct registers
        {
            perdo_register regA;
            perdo_register regB;
            perdo_register regC;
            perdo_register regD;
            perdo_register regE;
            perdo_register regF;
            perdo_register regG;
            perdo_register regH;
        };
        typedef struct registers registers;

        struct intvariable
        {
            int     block;      // Block in which this variable is first used
            int     refcount;   // Reference count for this variable
            bool    local;      // If the variable is only used in one block
            bool    dirty;      // If the variable needs to be written to memory
        };
        typedef struct intvariable intvariable;

        struct block_stats
        {
            int             block_count;// Number of blocks seen so far
            intvariable     *vars;      // Array of intvariable structures
        };
        typedef struct block_stats block_stats;

        // Miscellaneous member variables and methods
        void    flush_registers();      // Flushes register contents
        string  get_available_register(int);
        void    preprocess_blocks(string);
        string  parse_command(string);  // Translate int. command to assembly
        string  register_search(int);   // Searches registers for a memory pos.
        string  out_file;               // Where to store our assembly code
        vector<string> commands;        // Sequence of intermediate code
        block_stats blocks;             // Breakdown of int. code blocks
        int         current_time;       // Used during assembling
        registers   perdo_registers;    // Virtual registers
};

#endif /* ASSEMBLER_H */
