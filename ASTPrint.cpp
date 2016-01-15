/*
 *   ASTPrint.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTPrint.h"
using namespace std;

extern unsigned int var_count;
extern unsigned int label_count;
extern void add_int_command(string);

ASTPrint::ASTPrint(ASTNode *node1)
{
    this->lchild = node1;
    this->newline = false;
}

string ASTPrint::getType()
{
    return "<ASTPrint>";
}

void ASTPrint::setNewline(bool drop_newline)
{
    this->newline = drop_newline;
}

int ASTPrint::getValue()
{
}

void ASTPrint::genIntCode()
{
    lchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    if (lchild->getType() == "scalar" && lchild->getInternalType() == "number")
    {
        snprintf(int_command, MAXCMDLENGTH, "out_num s%d", lchild->getVarNum());
        add_int_command(int_command);
    }
    else if (lchild->getType() == "scalar" 
                && lchild->getInternalType() == "char")
    {
        snprintf(int_command, MAXCMDLENGTH, "out_char s%d", 
                    lchild->getVarNum());
        add_int_command(int_command);
    }
    else if (lchild->getType() == "array")
    {
        int size_register = var_count++;
        int pos_register = var_count++;
        int value_register = var_count++;
        int label_number = label_count++;
        
        snprintf(int_command, MAXCMDLENGTH, "array_get_size a%d s%d",
                    lchild->getVarNum(), size_register);
        add_int_command(int_command);

        snprintf(int_command, MAXCMDLENGTH, "val_copy 0 s%d", pos_register);
        add_int_command(int_command);
        
        snprintf(int_command, MAXCMDLENGTH, "array_print_start_%d:",
                    label_number);
        add_int_command(int_command);

        snprintf(int_command, MAXCMDLENGTH, "if_equ s%d s%d",
                    pos_register, size_register);
        add_int_command(int_command);

        snprintf(int_command, MAXCMDLENGTH, "jump array_print_end_%d",
                    label_number);
        add_int_command(int_command);

        snprintf(int_command, MAXCMDLENGTH, "array_get_index a%d s%d s%d",
                    lchild->getVarNum(), pos_register, value_register);
        add_int_command(int_command);

        if (lchild->getInternalType() == "number")
        {
            snprintf(int_command, MAXCMDLENGTH, "out_num s%d", value_register);
            add_int_command(int_command);
        }
        else
        {
            snprintf(int_command, MAXCMDLENGTH, "out_char s%d", value_register);
            add_int_command(int_command);
        }

        snprintf(int_command, MAXCMDLENGTH, "add s%d 1 s%d",
                    pos_register, pos_register);
        add_int_command(int_command);

        snprintf(int_command, MAXCMDLENGTH, "jump array_print_start_%d",
                    label_number);
        add_int_command(int_command);

        snprintf(int_command, MAXCMDLENGTH, "array_print_end_%d:",
                    label_number);
        add_int_command(int_command);
    }
    else if (lchild->getType() == "scalar" && lchild->getLvalue())
    {
        int value_register = var_count++;

        if (lchild->getInternalType() == "char")
        {
            snprintf(int_command, MAXCMDLENGTH, "out_char s%d",
                        lchild->getVarNum());
            add_int_command(int_command);
        }
        else
        {
            snprintf(int_command, MAXCMDLENGTH, "out_num s%d",
                        lchild->getVarNum());
            add_int_command(int_command);
        }
    }
    else
    {
        snprintf(int_command, MAXCMDLENGTH, "out_num s%d",
                        lchild->getVarNum());
        add_int_command(int_command);
    }
    
    if (this->newline)
    {
        snprintf(int_command, MAXCMDLENGTH, "out_char '\\n'");
        add_int_command(int_command);
    }
}
