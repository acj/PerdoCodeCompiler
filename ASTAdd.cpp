/*
 *   ASTAdd.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTAdd.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTAdd::ASTAdd(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != "scalar" 
        || node1->getInternalType() != "number"
        || node2->getType() != "scalar"
        || node2->getInternalType() != "number")
    {
        yyerror("Invalid operands to '+'");
    }

    this->lchild = node1;
    this->rchild = node2;
    this->var_num = var_count++;    
}

string ASTAdd::getType()
{
    return "scalar";
}

string ASTAdd::getInternalType()
{
    return "number";
}

void ASTAdd::genIntCode()
{
    lchild->genIntCode();
    rchild->genIntCode();
    
    char int_command[128];

    snprintf(int_command, 128, "add s%d s%d s%d", 
                lchild->getVarNum(), rchild->getVarNum(), this->var_num);

    add_int_command(int_command);
}

int ASTAdd::getValue()
{
}
