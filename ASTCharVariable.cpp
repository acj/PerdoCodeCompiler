/*
 *   ASTCharVariable.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTCharVariable.h"
#include "SymbolTable.h"
using namespace std;

ASTCharVariable::ASTCharVariable(string name, st_node *symtbl_entry)
{
    this->name = name;
    this->symtbl_entry = symtbl_entry;
    this->var_num = symtbl_entry->var_num;

#ifdef DEBUG
    cerr << "New ASTCharVariable (" << this->var_num << "):"
           << this->name << ", " << this->symtbl_entry->type << ":"
           << this->symtbl_entry->internal_type << endl;
#endif
}

string ASTCharVariable::getClass()
{
    return "ASTCharVariable";
}

string ASTCharVariable::getName()
{
    return this->name;
}

string ASTCharVariable::getType()
{
    return "scalar";
}

string ASTCharVariable::getInternalType()
{
    return "char";
}

void ASTCharVariable::genIntCode()
{
}

int ASTCharVariable::getValue()
{
}
