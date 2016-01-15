/*
 *   ASTValue.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTValue.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTValue::ASTValue(int value)
{
    this->var_num = var_count++;
    this->value = value;
}

string ASTValue::getClass()
{
    return "ASTValue";
}

string ASTValue::getType()
{
    return "scalar";
}

string ASTValue::getInternalType()
{
    return "number";
}

void ASTValue::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "val_copy %d s%d",
                this->value, this->var_num);
    add_int_command(int_command);
}

int ASTValue::getValue()
{
    return value;
}

ASTNode* ASTValue::leftChild()
{
    cerr << "leftChild() called on ASTValue node" << endl;
    return 0;
}

ASTNode* ASTValue::rightChild()
{
    cerr << "rightChild() called on ASTValue node" << endl;
    return 0;
}
