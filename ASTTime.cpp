/*
 *   ASTTime.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTTime.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTTime::ASTTime()
{
    this->var_num = var_count++;
}

string ASTTime::getType()
{
    return "scalar";
}

string ASTTime::getInternalType()
{
    return "number";
}

void ASTTime::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "time s%d", this->var_num);
    add_int_command(int_command);
}

int ASTTime::getValue()
{
    return value;
}

ASTNode* ASTTime::leftChild()
{
    cerr << "leftChild() called on ASTTime node" << endl;
    return 0;
}

ASTNode* ASTTime::rightChild()
{
    cerr << "rightChild() called on ASTTime node" << endl;
    return 0;
}
