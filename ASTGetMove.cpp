/*
 *   ASTGetMove.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTGetMove.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTGetMove::ASTGetMove()
{
    this->lchild = NULL;
    this->rchild = NULL;
    this->var_num = var_count++;
}

string ASTGetMove::getType()
{
    return "scalar";
}

string ASTGetMove::getInternalType()
{
    return "number";
}

void ASTGetMove::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "move_stat s%d", this->var_num);
    add_int_command(int_command);
}

int ASTGetMove::getValue()
{
    return value;
}

ASTNode* ASTGetMove::leftChild()
{
    cerr << "leftChild() called on ASTGetMove node" << endl;
    return 0;
}

ASTNode* ASTGetMove::rightChild()
{
    cerr << "rightChild() called on ASTGetMove node" << endl;
    return 0;
}
