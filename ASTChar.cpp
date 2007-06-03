/*
 *   ASTChar.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTChar.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTChar::ASTChar(char value)
{
    this->value = value;
    this->var_num = var_count++;
}

string ASTChar::getClass()
{
    return "ASTChar";
}

string ASTChar::getType()
{
    return "scalar";
}

string ASTChar::getInternalType()
{
    return "char";
}

void ASTChar::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "val_copy '%c' s%d",
                this->value, this->var_num);
    add_int_command(int_command);
}

int ASTChar::getValue()
{
}

char ASTChar::getCharValue()
{
    return value;
}

ASTNode* ASTChar::leftChild()
{
    cerr << "leftChild() called on ASTChar node" << endl;
    return 0;
}

ASTNode* ASTChar::rightChild()
{
    cerr << "rightChild() called on ASTChar node" << endl;
    return 0;
}
