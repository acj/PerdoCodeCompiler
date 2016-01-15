/*
 *   ASTSetShields.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTSetShields.h"
using namespace std;

extern void add_int_command(string);

ASTSetShields::ASTSetShields(ASTNode *node1)
{
    this->lchild = node1;
    this->rchild = NULL;
}

string ASTSetShields::getType()
{
    return "ASTSetShields";
}

int ASTSetShields::getValue()
{
}

void ASTSetShields::genIntCode()
{
    lchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "shields s%d", lchild->getVarNum());
    add_int_command(int_command);

}
