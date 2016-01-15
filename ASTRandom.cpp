/*
 *   ASTRandom.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTRandom.h"
using namespace std;

extern unsigned int var_count;
extern void yyerror(char *error_string, char *detail="");
extern void add_int_command(string);

ASTRandom::ASTRandom(ASTNode *node1)
{
    if (node1->getType() != "scalar" 
        || node1->getInternalType() != "number")
    {
        yyerror("Invalid argument to random");
    }

    this->lchild = node1;
    this->rchild = NULL;
    this->var_num = var_count++;
}

string ASTRandom::getType()
{
    return "scalar";
}

string ASTRandom::getInternalType()
{
    return "number";
}

void ASTRandom::genIntCode()
{
    lchild->genIntCode();
    
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "random s%d s%d",
                lchild->getVarNum(), this->var_num);
    add_int_command(int_command);
}

int ASTRandom::getValue()
{
}
