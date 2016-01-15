/*
 *   ASTGetEnergy.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTGetEnergy.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTGetEnergy::ASTGetEnergy()
{
    this->lchild = NULL;
    this->rchild = NULL;
    this->var_num = var_count++;
}

string ASTGetEnergy::getType()
{
    return "scalar";
}

string ASTGetEnergy::getInternalType()
{
    return "number";
}

void ASTGetEnergy::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "energy_stat s%d", this->var_num);
    add_int_command(int_command);
}

int ASTGetEnergy::getValue()
{
    return value;
}

ASTNode* ASTGetEnergy::leftChild()
{
    cerr << "leftChild() called on ASTGetEnergy node" << endl;
    return 0;
}

ASTNode* ASTGetEnergy::rightChild()
{
    cerr << "rightChild() called on ASTGetEnergy node" << endl;
    return 0;
}
