/*
 *   ASTFire.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTFire.h"
using namespace std;

extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTFire::ASTFire(ASTNode *node1)
{
    if (node1->getType() != "scalar" || node1->getInternalType() != "number")
    {
        yyerror("Invalid operand to fire");
    }

    this->lchild = node1;
    this->rchild = NULL;
}

string ASTFire::getType()
{
    return "<ASTFire>";
}

int ASTFire::getValue()
{
}

void ASTFire::genIntCode()
{
    lchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "fire s%d", lchild->getVarNum());
    add_int_command(int_command);
}
