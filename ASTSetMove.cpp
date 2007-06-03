/*
 *   ASTSetMove.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTSetMove.h"
using namespace std;

extern void add_int_command(string);

ASTSetMove::ASTSetMove(ASTNode *node1)
{
    this->lchild = node1;
    this->rchild = NULL;
}

string ASTSetMove::getType()
{
    return "ASTSetMove";
}

int ASTSetMove::getValue()
{
}

void ASTSetMove::genIntCode()
{
    lchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "move s%d", lchild->getVarNum());
    add_int_command(int_command);

}
