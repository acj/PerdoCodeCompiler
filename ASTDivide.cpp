/*
 *   ASTDivide.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTDivide.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTDivide::ASTDivide(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != "scalar" || node2->getType() != "scalar")
    {
        yyerror("Invalid operand to '/'");
    }

    this->lchild = node1;
    this->rchild = node2;
    this->var_num = var_count++;
}

string ASTDivide::getType()
{
    return "scalar";
}

string ASTDivide::getInternalType()
{
    return "number";
}

void ASTDivide::genIntCode()
{
    lchild->genIntCode();
    rchild->genIntCode();
    
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "div s%d s%d s%d",
                lchild->getVarNum(), rchild->getVarNum(), this->var_num);
    add_int_command(int_command);
}

int ASTDivide::getValue()
{
}
