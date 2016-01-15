/*
 *   ASTArray.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTArray.h"
using namespace std;

extern unsigned int var_count;

ASTArray::ASTArray(string name, st_node *symtbl_entry)
{
    this->name = name;
    this->symtbl_entry = symtbl_entry;
    this->var_num = symtbl_entry->var_num;
}

string ASTArray::getType()
{
    return "array";
}

string ASTArray::getInternalType()
{
    return symtbl_entry->internal_type;
}

void ASTArray::setInternalType(string new_type)
{
    symtbl_entry->internal_type = new_type;
}

void ASTArray::genIntCode()
{
}

int ASTArray::getValue()
{
}

bool ASTArray::getLvalue()
{
    return this->lvalue;
}

void ASTArray::setLvalue(bool new_value)
{
    this->lvalue = new_value;
}

ASTNode* ASTArray::leftChild()
{
    cerr << "leftChild() called on ASTArray node" << endl;
    return 0;
}

ASTNode* ASTArray::rightChild()
{
    cerr << "rightChild() called on ASTArray node" << endl;
    return 0;
}
