/*
 *   ASTVariable.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTVariable.h"
#include "SymbolTable.h"
using namespace std;

ASTVariable::ASTVariable(string name, st_node *symtbl_entry)
{
    this->name = name;
    this->symtbl_entry = symtbl_entry;
    this->var_num = symtbl_entry->var_num;

#ifdef DEBUG
    cerr << "New ASTVariable (" << this->var_num << "):"
           << this->name << ", " << this->symtbl_entry->type << ":"
           << this->symtbl_entry->internal_type << endl;
#endif
}

string ASTVariable::getClass()
{
    return "ASTVariable";
}

string ASTVariable::getName()
{
    return this->name;
}

string ASTVariable::getType()
{
    return "scalar";
}

string ASTVariable::getInternalType()
{
    return "number";
}

void ASTVariable::genIntCode()
{
}

int ASTVariable::getValue()
{
}
