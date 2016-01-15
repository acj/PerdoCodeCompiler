/*
 *   ASTGetShields.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTGetShields.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTGetShields::ASTGetShields()
{
    this->lchild = NULL;
    this->rchild = NULL;
    this->var_num = var_count++;
}

string ASTGetShields::getType()
{
    return "scalar";
}

string ASTGetShields::getInternalType()
{
    return "number";
}

void ASTGetShields::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "shield_stat s%d", this->var_num);
    add_int_command(int_command);
}

int ASTGetShields::getValue()
{
    return value;
}

ASTNode* ASTGetShields::leftChild()
{
    cerr << "leftChild() called on ASTGetShields node" << endl;
    return 0;
}

ASTNode* ASTGetShields::rightChild()
{
    cerr << "rightChild() called on ASTGetShields node" << endl;
    return 0;
}
