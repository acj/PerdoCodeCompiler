/*
 *   ASTNotEqual.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTNotEqual.h"
using namespace std;

extern unsigned int var_count;
extern void yyerror(char *error_string, char *detail="");
extern void add_int_command(string);

ASTNotEqual::ASTNotEqual(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != node2->getType()
        || node1->getInternalType() != node2->getInternalType())
    {
        yyerror("Invalid operands to '!='");
    }
    
    this->lchild = node1;
    this->rchild = node2;
    this->var_num = var_count++;  
}

string ASTNotEqual::getType()
{
    return "scalar";
}

string ASTNotEqual::getInternalType()
{
    return "number";
}

void ASTNotEqual::genIntCode()
{
    lchild->genIntCode();
    rchild->genIntCode();
    
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "if_n_equ s%d s%d s%d",
                lchild->getVarNum(), rchild->getVarNum(), this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "nop");
    add_int_command(int_command);
}

int ASTNotEqual::getValue()
{
}
