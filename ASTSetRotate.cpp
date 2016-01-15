/*
 *   ASTSetRotate.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTSetRotate.h"
using namespace std;

extern void add_int_command(string);

ASTSetRotate::ASTSetRotate(ASTNode *node1)
{
    this->lchild = node1;
    this->rchild = NULL;
}

string ASTSetRotate::getType()
{
    return "ASTSetRotate";
}

int ASTSetRotate::getValue()
{
}

void ASTSetRotate::genIntCode()
{
    lchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "rotate s%d", lchild->getVarNum());
    add_int_command(int_command);
}
