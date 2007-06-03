/*
 *   ASTAnd.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTAnd.h"
using namespace std;

extern unsigned int var_count, label_count;
extern void yyerror(char *error_string, char *detail="");
extern void add_int_command(string);

ASTAnd::ASTAnd(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != "scalar" || node2->getType() != "scalar"
        || node1->getInternalType() != "number"
        || node2->getInternalType() != "number")
        yyerror("Invalid operands to boolean");

    this->lchild = node1;
    this->rchild = node2;
    this->var_num = var_count++;    
}

string ASTAnd::getType()
{
    return "scalar";
}

string ASTAnd::getInternalType()
{
    return "number";
}

void ASTAnd::genIntCode()
{
    lchild->genIntCode();
    rchild->genIntCode();
    
    char int_command[MAXCMDLENGTH];
    
    snprintf(int_command, MAXCMDLENGTH, "val_copy 0 s%d", this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_equ s%d 0", lchild->getVarNum());
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump and_end_%d", label_count);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_n_equ s%d 0 s%d", 
                rchild->getVarNum(), this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "val_copy 1 s%d", this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "and_end_%d:", label_count++);
    add_int_command(int_command);
}

int ASTAnd::getValue()
{
}

