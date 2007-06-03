/*
 *   ASTGetRotate.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTGetRotate.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTGetRotate::ASTGetRotate()
{
    this->lchild = NULL;
    this->rchild = NULL;
    this->var_num = var_count++;
}

string ASTGetRotate::getType()
{
    return "scalar";
}

string ASTGetRotate::getInternalType()
{
    return "number";
}

void ASTGetRotate::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "rotate_stat s%d", this->var_num);
    add_int_command(int_command);
}

int ASTGetRotate::getValue()
{
    return value;
}

ASTNode* ASTGetRotate::leftChild()
{
    cerr << "leftChild() called on ASTGetRotate node" << endl;
    return 0;
}

ASTNode* ASTGetRotate::rightChild()
{
    cerr << "rightChild() called on ASTGetRotate node" << endl;
    return 0;
}
