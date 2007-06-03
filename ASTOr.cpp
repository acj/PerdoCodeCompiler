/*
 *   ASTOr.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTOr.h"
using namespace std;

extern unsigned int var_count, label_count;
extern void yyerror(char *error_string, char *detail="");
extern void add_int_command(string);

ASTOr::ASTOr(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != "scalar" || node2->getType() != "scalar"
        || node1->getInternalType() != "number"
        || node2->getInternalType() != "number")
        yyerror("Invalid operands to '||'");

    this->lchild = node1;
    this->rchild = node2;
    this->var_num = var_count++;    
}

string ASTOr::getType()
{
    return "scalar";
}

string ASTOr::getInternalType()
{
    return "number";
}

void ASTOr::genIntCode()
{
    lchild->genIntCode();
    rchild->genIntCode();
    
    char int_command[MAXCMDLENGTH];
    
    snprintf(int_command, MAXCMDLENGTH, "if_n_equ s%d 0 s%d",
                lchild->getVarNum(), this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump or_true_%d", label_count);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_n_equ s%d 0 s%d",
                rchild->getVarNum(), this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "nop");
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "or_true_%d:", label_count++);
    add_int_command(int_command);
}

int ASTOr::getValue()
{
}
