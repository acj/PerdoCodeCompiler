/*
 *   ASTString.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTString.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTString::ASTString(string value, st_node *sym)
{
    this->value = value;
    this->var_num = var_count++;
    sym->var_num = this->var_num;
}

string ASTString::getType()
{
    return "array";
}

string ASTString::getInternalType()
{
    return "char";
}

void ASTString::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "array_set_size a%d %d",
                this->var_num, value.length());
    add_int_command(int_command);

    int i;
    for (i = 0; i < value.length(); i++)
    {
        snprintf(int_command, MAXCMDLENGTH, "array_set_index a%d %d '%c'",
                    this->var_num, i, value[i]);
        add_int_command(int_command);
    }
}

int ASTString::getValue()
{
}

string ASTString::getStringValue()
{
    return value;
}

ASTNode* ASTString::leftChild()
{
    cerr << "leftChild() called on ASTString node" << endl;
    return 0;
}

ASTNode* ASTString::rightChild()
{
    cerr << "rightChild() called on ASTString node" << endl;
    return 0;
}
