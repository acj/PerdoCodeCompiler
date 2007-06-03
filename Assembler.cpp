/*
 *   Assembler.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "Assembler.h"
#include "common.h"
#include "SymbolTable.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

extern unsigned int var_count;

Assembler::Assembler(string out_file)
{
    this->out_file = out_file;
    this->blocks.block_count = 1;
    this->current_time = 1;

    // Initialize registers
    this->perdo_registers.regA.mem_pos = -1;
    this->perdo_registers.regB.mem_pos = -1;
    this->perdo_registers.regC.mem_pos = -1;
    this->perdo_registers.regD.mem_pos = -1;
    this->perdo_registers.regE.mem_pos = -1;
    this->perdo_registers.regF.mem_pos = -1;
    this->perdo_registers.regG.mem_pos = -1;
    this->perdo_registers.regH.mem_pos = -1;
    this->perdo_registers.regA.time = 0;
    this->perdo_registers.regB.time = 0;
    this->perdo_registers.regC.time = 0;
    this->perdo_registers.regD.time = 0;
    this->perdo_registers.regE.time = 0;
    this->perdo_registers.regF.time = 0;
    this->perdo_registers.regG.time = 0;
    this->perdo_registers.regH.time = 0;
}

void Assembler::preprocess_blocks(string command)
{
    vector<string> tokens = tokenize_string(command);

    if (tokens[0] == "add" || tokens[0] == "sub" || tokens[0] == "mult" ||
        tokens[0] == "div" || tokens[0] == "mod")
    {
    }
    else if (tokens[0] == "val_copy")
    {
    }
    else if (tokens[0] == "if_less" || tokens[0] == "if_gtr" ||
             tokens[0] == "if_equ" || tokens[0] == "if_n_equ" ||
             tokens[0] == "if_less_equ" || tokens[0] == "if_gtr_equ")
    {
        this->blocks.block_count++;
    }
    else if (tokens[0] == "array_set_size")
    {
    }
    else if (tokens[0] == "array_copy")
    {
    }
    else if (tokens[0] == "jump" && tokens[1].substr(0, 1) == "s")
    {
        this->blocks.block_count += 1;
    }
    else
    {
        this->blocks.block_count += 1;
    }
        
    if (tokens.size() == 2)
    {
        if (tokens[0] == "jump" && tokens[1].substr(0, 1) == "s")
        {
            int arg = atoi(tokens[1].substr(1, tokens[1].length()-1).c_str());

            if (this->blocks.vars[arg].block != 0
                && this->blocks.vars[arg].block != this->blocks.block_count)
            {
                this->blocks.vars[arg].local = false;
            }
            else
            {
                this->blocks.vars[arg].block = this->blocks.block_count;
                this->blocks.vars[arg].local = true;
            }
        }
    }
    if (tokens.size() == 3)
    {
        int arg1, arg2;
        
        if (tokens[1][0] == 's')
        {
            arg1 = atoi(tokens[1].substr(1, tokens[1].length()-1).c_str());

            if (this->blocks.vars[arg1].block != 0
                && this->blocks.vars[arg1].block != this->blocks.block_count)
            {
                this->blocks.vars[arg1].local = false;
            }
            else
            {
                this->blocks.vars[arg1].block = this->blocks.block_count;
                this->blocks.vars[arg1].local = true;
            }
        }

        if (tokens[2][0] == 's')
        {
            arg2 = atoi(tokens[2].substr(1, tokens[2].length()-1).c_str());

            if (this->blocks.vars[arg2].block != 0
                && this->blocks.vars[arg2].block != this->blocks.block_count)
            {
                this->blocks.vars[arg2].local = false;
            }
            else
            {
                this->blocks.vars[arg2].block = this->blocks.block_count;
                this->blocks.vars[arg2].local = true;
            }
        }
    } 
    else if (tokens.size() == 4)
    {
        if (tokens[3][0] == 's')
        {
            int arg3 = atoi(tokens[3].substr(1, tokens[3].length()-1).c_str());

            if (this->blocks.vars[arg3].block != 0
                && this->blocks.vars[arg3].block != this->blocks.block_count)
            {
                this->blocks.vars[arg3].local = false;
                this->blocks.vars[arg3].dirty = true;
            }
            else
            {
                this->blocks.vars[arg3].block = this->blocks.block_count;
                this->blocks.vars[arg3].local = true;
                this->blocks.vars[arg3].dirty = true;
            }
        }
    }
}

// Parse and translate an intermediate code sequence into assembly
string Assembler::parse_command(string command)
{
    static int current_block = 1;

    vector<string> tokens = tokenize_string(command);
    string assembled = "";
    string reg1 = "";
    string reg2 = "";
    string reg3 = "";
    string var = "";

    if (tokens[0] == "add" || tokens[0] == "sub" || tokens[0] == "mult" ||
        tokens[0] == "div" || tokens[0] == "mod")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# Arithmetic\n";
	#endif

        if (tokens[1].substr(0,1) == "s")
        {
            var = tokens[1].substr(1, tokens[1].length()-1);
            reg1 = register_search(atoi(var.c_str()));

            if (reg1 == "")
                reg1 = get_available_register(atoi(var.c_str()));
         
            assembled += "load " + var + " " + reg1 + "\n";
        }
        else
        {
            reg1 = get_available_register(-1);
            assembled += "val_copy " + tokens[1] + " " + reg1 + "\n";
        }

        if (tokens[2].substr(0,1) == "s")
        {
            var = tokens[2].substr(1, tokens[2].length()-1);
            reg2 = register_search(atoi(var.c_str()));

            if (reg2 == "")
                reg2 = get_available_register(atoi(var.c_str()));
            
            assembled += "load " + var + " " + reg2 + "\n";
        }
        else
        {
            reg2 = get_available_register(-1);
            assembled += "val_copy " + tokens[2] + " " + reg2 + "\n";
        }

        var = tokens[3].substr(1, tokens[3].length()-1);
        reg3 = get_available_register(atoi(var.c_str()));

        assembled += tokens[0] + " " + reg1 + " " + reg2 + " " + reg3 + "\n"; 
        assembled += "store " + reg3 + " " + var + "\n";
    }
    else if (tokens[0] == "val_copy")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# val_copy\n";
	#endif

        if (tokens[1].substr(0,1) == "s")
        {
            var = tokens[1].substr(1, tokens[1].length()-1);
            reg1 = register_search(atoi(var.c_str()));

            string var2 = tokens[2].substr(1, tokens[2].length()-1);
            reg2 = register_search(atoi(var2.c_str()));

            if (reg1 == "")
                reg1 = get_available_register(atoi(var.c_str()));

            // If the destination is currently in a register, we can
            // use the register to preserve its correct state.
            if (reg2 != "")
            {
                assembled += "load " + var + " " + reg2 + "\n";
                assembled += "store " + reg2 + " " + var2 + "\n";
            }
            else
            {
                assembled += "mem_copy " + var + " " + var2 + "\n";
            }
        }
        else if (tokens[1] == "'")
        {
            var = tokens[3].substr(1, tokens[3].length()-1);
            assembled += "store ' ' " + var + "\n";
        }
        else
        {
            var = tokens[2].substr(1, tokens[2].length()-1);
            assembled += "store " + tokens[1] + " " + var + "\n";
        }
    }
    else if (tokens[0] == "if_less" || tokens[0] == "if_gtr" ||
             tokens[0] == "if_equ" || tokens[0] == "if_n_equ" ||
             tokens[0] == "if_less_equ" || tokens[0] == "if_gtr_equ")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# Conditionals\n";
	#endif

        current_block++;
        flush_registers();

        if (tokens[1].substr(0,1) == "s")
            assembled += "load " + tokens[1].substr(1,tokens[1].size()-1);
        else
            assembled += "load " + tokens[1];

        assembled += " regA\n";

        if (tokens[2].substr(0,1) == "s")
            assembled += "load " + tokens[2].substr(1,tokens[2].size()-1);
        else
            assembled += "val_copy " + tokens[2];

        assembled += " regB\n" 
                + tokens[0] + " regA regB";

        if (tokens.size() == 4)
        {
            assembled += " regC\n";
            assembled += "nop\n";
            assembled += "store regC " + tokens[3].substr(1,tokens[3].size()-1)
                    + "\n";
            assembled += "if_equ regC 1\n";
        }
        else
            assembled += "\n";

        current_block++;
        flush_registers();
    }
    else if (tokens[0] == "out_num")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# out_num\n";
	#endif

        if (tokens[1].substr(0, 1) == "s")
        {
            var = tokens[1].substr(1, tokens[1].size()-1);
            reg1 = register_search(atoi(var.c_str()));

            if (reg1 == "")
            {
                reg1 = get_available_register(atoi(var.c_str()));
            
                assembled += "load " + var + " " + reg1 + "\n";
            }

            assembled += "out_num " + reg1 + "\n";
        }
        else assembled += command + "\n";
    }
    else if (tokens[0] == "out_char")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# out_char\n";
	#endif

        if (tokens[1].substr(0, 1) == "s")
        {
            var = tokens[1].substr(1, tokens[1].size()-1);
            reg1 = register_search(atoi(var.c_str()));

            if (reg1 == "")
            {
                reg1 = get_available_register(atoi(var.c_str()));
            
                assembled += "load " + var + " " + reg1 + "\n";
            }

            assembled += "out_char " + reg1 + "\n";
        }
        else assembled += command + "\n";
    }
    else if (tokens[0] == "err_num")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# err_num\n";
	#endif

        if (tokens[1].substr(0, 1) == "s")
        {
            var = tokens[1].substr(1, tokens[1].size()-1);
            reg1 = register_search(atoi(var.c_str()));

            if (reg1 == "")
            {
                reg1 = get_available_register(atoi(var.c_str()));
            
                assembled += "load " + var + " " + reg1 + "\n";
            }

            assembled += "err_num " + reg1 + "\n";
        }
        else assembled += command + "\n";
    }
    else if (tokens[0] == "err_char")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# err_char\n";
	#endif

        if (tokens[1].substr(0, 1) == "s")
        {
            var = tokens[1].substr(1, tokens[1].size()-1);
            reg1 = register_search(atoi(var.c_str()));

            if (reg1 == "")
            {
                reg1 = get_available_register(atoi(var.c_str()));
            
                assembled += "load " + var + " " + reg1 + "\n";
            }

            assembled += "err_char " + reg1 + "\n";
        }
        else assembled += command + "\n";
    }
    else if (tokens[0] == "fire" || tokens[0] == "move" ||
             tokens[0] == "rotate" || tokens[0] == "shields")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# Robot control (1)\n";
	#endif

        assembled += "load " + tokens[1].substr(1, tokens[1].length()-1) 
                + " regA\n" + tokens[0] + " regA\n";
    }
    else if (tokens[0] == "scan")
    {
        assembled += string("scan regA regB regC\n")
                + "store regA " + tokens[1].substr(1,
                    tokens[1].length()-1) + "\n" 
                + "store regB " + tokens[2].substr(1,
                    tokens[2].length()-1) + "\n" 
                + "store regC " + tokens[3].substr(1,
                    tokens[3].length()-1) + "\n";
    }
    else if (tokens[0] == "move_stat" || tokens[0] == "rotate_stat" ||
             tokens[0] == "shield_stat" || tokens[0] == "energy_stat")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# Robot control (scan)\n";
	#endif

        assembled += tokens[0] + " regA\n" 
                + "store regA " 
                + tokens[1].substr(1, tokens[1].length()-1) + "\n";
    }
    else if (tokens[0] == "array_get_index")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# array_get_index\n";
	#endif

        var = tokens[1].substr(1, tokens[1].length()-1);
        reg1 = register_search(atoi(var.c_str()));

        if (reg1 == "")
        {
            reg1 = get_available_register(atoi(var.c_str()));
            assembled += "load " + var + " " + reg1 + "\n";
        }

        var = tokens[2].substr(1, tokens[2].length()-1);
        reg2 = register_search(atoi(var.c_str()));

        if (reg2 == "")
        {
            reg2 = get_available_register(atoi(var.c_str()));
            assembled += "load " + var + " " + reg2 + "\n";
        }

        // Dummy register for handling positions
        reg3 = get_available_register(-1);

        assembled += "add " + reg1 + " 1 " + reg3 + "\n"
                + "add " + reg3 + " " + reg2 + " " + reg3 + "\n";
                
        var = tokens[3].substr(1,tokens[3].length()-1);
        assembled += "mem_copy " + reg3 + " " + var + "\n";
    }
    else if (tokens[0] == "array_set_index")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# array_set_index\n";
	#endif

        var = tokens[1].substr(1, tokens[1].length()-1);
        reg1 = register_search(atoi(var.c_str()));

        if (reg1 == "")
        {
            reg1 = get_available_register(atoi(var.c_str()));
            assembled += "load " + var + " " + reg1 + "\n";
        }

        var = tokens[2].substr(1, tokens[2].length()-1);

        if (tokens[2].substr(0,1) == "s")
        {
            reg2 = register_search(atoi(var.c_str()));

            if (reg2 == "")
            {
                reg2 = get_available_register(atoi(var.c_str()));
                assembled += "load " + var + " " + reg2 + "\n";
            }
        }
        else
        {
            reg2 = get_available_register(atoi(var.c_str()));
            assembled += "val_copy " + tokens[2] + " " + reg2 + "\n";
        }
                
        // Dummy register for handling positions
        reg3 = get_available_register(-1);

        assembled += "add " + reg1 + " 1 " + reg3 + "\n"
                + "add " + reg3 + " " + reg2 + " " + reg3 + "\n";
        
        var = tokens[3].substr(1,tokens[3].length()-1);

        if (tokens[3].substr(0,1) == "s")
        {
            assembled += "mem_copy " + var;
        }
        else if (tokens[3] == "'") // Fix for literal space
            assembled += "store ' '";
        else
            assembled += "store " + tokens[3];
        
        assembled += " " + reg3 + "\n";
    }
    else if (tokens[0] == "array_get_size")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# array_get_size\n";
	#endif
                    
        assembled += "load " + tokens[1].substr(1, tokens[1].length()-1)
                + " regA\n"
                + "load regA regB\n"
                + "store regB " + tokens[2].substr(1, tokens[2].length()-1)
                + "\n";
    }
    else if (tokens[0] == "array_set_size")
    {
        #ifdef DEBUG_ASSEMBLER
        assembled += "# array_set_size\n";
        #endif
        
        current_block++;
        flush_registers();

        assembled += "load " + tokens[1].substr(1, tokens[1].length()-1)
                + " regA\n";

        if (tokens[2].substr(0,1) == "s")
            assembled += "load " + tokens[2].substr(1, tokens[2].length()-1)
                    + " regB\n";
        else
            assembled += "val_copy " + tokens[2] + " regB\n";

        assembled += string("load regA regC\n")
                + "if_less regB regC\n"
                + "store regB regA\n"
                + "if_less_equ regB regC\n"
                + "jump array_resize_end_" 
                    + tokens[1].substr(1,tokens[1].length()-1) + "\n"
                + "load 0 regD\n"
                + "add regD regB regE\n"
                + "add regE 1 regE\n"
                + "store regE 0\n"
                + "store regD " + tokens[1].substr(1,tokens[1].length()-1)
                    + "\n"
                + "store regB regD\n"
                + "add regA regC regE\n"
                + "array_resize_start_" 
                    + tokens[1].substr(1,tokens[1].length()-1) + ":\n"
                + "add regA 1 regA\n"
                + "add regD 1 regD\n"
                + "if_gtr regA regE\n"
                + "jump array_resize_end_"
                    + tokens[1].substr(1,tokens[1].length()-1) + "\n"
                + "mem_copy regA regD\n"
                + "jump array_resize_start_"
                    + tokens[1].substr(1,tokens[1].length()-1) + "\n"
                + "array_resize_end_" + tokens[1].substr(1,tokens[1].length()-1)
                    + ":\n";

        current_block++;
        flush_registers();
    }
    else if (tokens[0] == "array_copy")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# array_copy\n";
	#endif

        current_block++;
        flush_registers();

        assembled += "load " + tokens[1].substr(1, tokens[1].length()-1)
                + " regA\n"
                + "load " + tokens[2].substr(1, tokens[2].length()-1)
                + " regB\n"
                + "load regA regC\n"    // Get size of old array
                + "load 0 regD\n"       // Get next available memory
                + "store regD " + tokens[2].substr(1, tokens[2].length()-1)
                    + "\n"
                + "store regC regD\n" 
                + "val_copy 0 regE\n"   // Stopping index for copy
                + "array_copy_start_" 
                    + tokens[1].substr(1, tokens[1].length()-1) + ":\n"
                + "if_equ regE regC\n"
                + "jump array_copy_end_"
                    + tokens[1].substr(1, tokens[1].length()-1) + "\n"
                + "add regA 1 regA\n"
                + "add regD 1 regD\n"
                + "add regE 1 regE\n"
                + "mem_copy regA regD\n"
                + "jump array_copy_start_"
                    + tokens[1].substr(1, tokens[1].length()-1) + "\n"
                + "array_copy_end_"
                    + tokens[1].substr(1, tokens[1].length()-1) + ":\n"
                + "add regD 1 regD\n"
                + "store regD 0\n";

        current_block++;
        flush_registers();
    }
    else if (tokens[0] == "random")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# random\n";
	#endif

        var = tokens[1].substr(1, tokens[1].length()-1);
        reg1 = register_search(atoi(var.c_str()));

        if (reg1 == "")
        {
            reg1 = get_available_register(atoi(var.c_str()));
            assembled += "load " + var + " " + reg1 + "\n";
        }

        var = tokens[2].substr(1, tokens[2].length()-1) + "\n";
        reg2 = get_available_register(atoi(var.c_str()));

        assembled += "random " + reg1 + " " + reg2 + "\n";
        assembled += "store " + reg2 + " " + var + "\n"; 
        
    }
    else if (tokens[0] == "time")
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# time\n";
	#endif

        // Use oldest register first
        reg1 = get_available_register(atoi(var.c_str()));

        assembled += "time " + reg1 + "\n"; 
        
        assembled += "store " + reg1 + " "
                + tokens[1].substr(1, tokens[1].length()-1) + "\n";
    }
    else if (tokens[0] == "jump" && tokens[1].substr(0, 1) == "s")
    {
        #ifdef DEBUG_ASSEMBLER
        assembled += "# jump to register\n";
        #endif

        // No need for optimization here because we're flushing the
        // registers.
        current_block++;
        flush_registers();

        assembled += "load " + tokens[1].substr(1, tokens[1].length()-1)
                + " regA\n" 
                + "jump regA\n";
    }
    else
    {
	#ifdef DEBUG_ASSEMBLER
        assembled += "# Literal\n";
	#endif

        flush_registers();

        assembled += command + "\n";
    }
            
    return assembled;
}

void Assembler::flush_registers()
{
    this->perdo_registers.regA.mem_pos = -1;
    this->perdo_registers.regB.mem_pos = -1;
    this->perdo_registers.regC.mem_pos = -1;
    this->perdo_registers.regD.mem_pos = -1;
    this->perdo_registers.regE.mem_pos = -1;
    this->perdo_registers.regF.mem_pos = -1;
    this->perdo_registers.regG.mem_pos = -1;
    this->perdo_registers.regH.mem_pos = -1;
    this->perdo_registers.regA.time = 0;
    this->perdo_registers.regB.time = 0;
    this->perdo_registers.regC.time = 0;
    this->perdo_registers.regD.time = 0;
    this->perdo_registers.regE.time = 0;
    this->perdo_registers.regF.time = 0;
    this->perdo_registers.regG.time = 0;
    this->perdo_registers.regH.time = 0;
}

// Search registers for a specific memory position
//
// Returns -1 if the position is not in any register
// Returns the register
string Assembler::register_search(int memory_pos)
{
    if (this->perdo_registers.regA.mem_pos == memory_pos)
    {
        this->perdo_registers.regA.time = current_time;
        return "regA";
    }
    else if (this->perdo_registers.regB.mem_pos == memory_pos)
    {
        this->perdo_registers.regB.time = current_time;
        return "regB";
    }
    else if (this->perdo_registers.regC.mem_pos == memory_pos)
    {
        this->perdo_registers.regC.time = current_time;
        return "regC";
    }
    else if (this->perdo_registers.regD.mem_pos == memory_pos)
    {
        this->perdo_registers.regD.time = current_time;
        return "regD";
    }
    else if (this->perdo_registers.regE.mem_pos == memory_pos)
    {
        this->perdo_registers.regE.time = current_time;
        return "regE";
    }
    else if (this->perdo_registers.regF.mem_pos == memory_pos)
    {
        this->perdo_registers.regF.time = current_time;
        return "regF";
    }
    else if (this->perdo_registers.regG.mem_pos == memory_pos)
    {
        this->perdo_registers.regG.time = current_time;
        return "regG";
    }
    else if (this->perdo_registers.regH.mem_pos == memory_pos)
    {
        this->perdo_registers.regH.time = current_time;
        return "regH";
    }
    else
        return "";
}

string Assembler::get_available_register(int memory_pos)
{
    this->current_time++;

    // Find the register that has been stored the longest and replace
    // its contents with the memory position that we seek.
    int  lowest_time = perdo_registers.regA.time;
    int *register_value = &perdo_registers.regA.mem_pos;
    int *register_time = &perdo_registers.regA.time;
    string  lowest_register = "regA";

    if (perdo_registers.regB.time < lowest_time)
    {
        lowest_time = perdo_registers.regB.time;
        register_value = &perdo_registers.regB.mem_pos;
        register_time = &perdo_registers.regB.time;
        lowest_register = "regB";
    }
    
    if (perdo_registers.regC.time < lowest_time)
    {
        lowest_time = perdo_registers.regC.time;
        register_value = &perdo_registers.regC.mem_pos;
        register_time = &perdo_registers.regC.time;
        lowest_register = "regC";
    }

    if (perdo_registers.regD.time < lowest_time)
    {
        lowest_time = perdo_registers.regD.time;
        register_value = &perdo_registers.regD.mem_pos;
        register_time = &perdo_registers.regD.time;
        lowest_register = "regD";
    }

    if (perdo_registers.regE.time < lowest_time)
    {
        lowest_time = perdo_registers.regE.time;
        register_value = &perdo_registers.regE.mem_pos;
        register_time = &perdo_registers.regE.time;
        lowest_register = "regE";
    }

    if (perdo_registers.regF.time < lowest_time)
    {
        lowest_time = perdo_registers.regF.time;
        register_value = &perdo_registers.regF.mem_pos;
        register_time = &perdo_registers.regF.time;
        lowest_register = "regF";
    }

    if (perdo_registers.regG.time < lowest_time)
    {
        lowest_time = perdo_registers.regG.time;
        register_value = &perdo_registers.regG.mem_pos;
        register_time = &perdo_registers.regG.time;
        lowest_register = "regG";
    }

    if (perdo_registers.regH.time < lowest_time)
    {
        //lowest_time = registers.regH.time;
        register_value = &perdo_registers.regH.mem_pos;
        register_time = &perdo_registers.regH.time;
        lowest_register = "regH";
    }

    /*
     cerr << perdo_registers.regA.time << "\t" << perdo_registers.regA.mem_pos << endl;
    cerr << perdo_registers.regB.time << "\t" << perdo_registers.regB.mem_pos << endl;
    cerr << perdo_registers.regC.time  << "\t" << perdo_registers.regC.mem_pos << endl;
    cerr << perdo_registers.regD.time << "\t" << perdo_registers.regD.mem_pos  << endl;
    cerr << perdo_registers.regE.time << "\t" << perdo_registers.regE.mem_pos  << endl;
    cerr << perdo_registers.regF.time << "\t" << perdo_registers.regF.mem_pos  << endl;
    cerr << perdo_registers.regG.time << "\t" << perdo_registers.regG.mem_pos  << endl;
    cerr << perdo_registers.regH.time << "\t" << perdo_registers.regH.mem_pos  << endl << endl;
    */

    *register_value = memory_pos;
    *register_time = this->current_time; 
    return lowest_register;
}

// Output intermediate code instead of assembly
void Assembler::output_intermediate()
{
    // Set up i/o to produce assembly output
    ofstream perdo_out;
    perdo_out.open(this->out_file.c_str());

    if (!perdo_out.is_open())
    {
        cerr << "Error opening " << this->out_file << endl;
        exit(1);
    }

    vector<string>::const_iterator c_iter;
    
    for (c_iter = this->commands.begin(); 
            c_iter != this->commands.end();
            c_iter++)
    {
        perdo_out << *c_iter << endl;
    }

    perdo_out.close();
}

// Translate and output assembly code
void Assembler::translate()
{
    // First, perform our optimization steps
    vector<string>::const_iterator c_iter;
    
    // Initialize storage for our variable statistics.  This MUST be done
    // AFTER the correct number of intermediate variables is known.
    //this->blocks.vars = (intvariable *)calloc(var_count, sizeof(intvariable));

    /*
    for (c_iter = this->commands.begin(); 
            c_iter != this->commands.end();
            c_iter++)
    {
        preprocess_blocks(*c_iter);
    }
    */

    // Set up i/o to produce assembly output
    ofstream perdo_out;
    perdo_out.open(this->out_file.c_str());

    if (!perdo_out.is_open())
    {
        cerr << "Error opening " << this->out_file << endl;
        exit(1);
    }

    unsigned freemem_start = var_count;
    vector<int> arrays = sym_get_arrays();
    vector<int>::const_iterator iter;
    for (iter = arrays.begin(); iter != arrays.end(); iter++)
    {
        perdo_out << "store " << freemem_start << " " << *iter << endl;
        perdo_out << "store " << 0 << " " << freemem_start << endl;

        freemem_start++;
    }

    perdo_out << "store " << freemem_start << " 0" << endl;

    for (c_iter = this->commands.begin(); 
            c_iter != this->commands.end();
            c_iter++)
    {
        perdo_out << parse_command(*c_iter);
    }

    perdo_out.close();
}
