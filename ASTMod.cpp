/*
 *   ASTMod.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTMod.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTMod::ASTMod(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != "scalar" || node2->getType() != "scalar"
        || node1->getInternalType() != "number"
        || node2->getInternalType() != "number")
    {
        yyerror("Invalid operand to 'mod'");
    }

    this->lchild = node1;
    this->rchild = node2;
    this->var_num = var_count++;
}

string ASTMod::getType()
{
    return "scalar";
}

string ASTMod::getInternalType()
{
    return "number";
}

void ASTMod::genIntCode()
{
    lchild->genIntCode();
    rchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "mod s%d s%d s%d",
                lchild->getVarNum(), rchild->getVarNum(), this->var_num);
    add_int_command(int_command);
}

int ASTMod::getValue()
{
}
