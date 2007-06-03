/*
 *   ASTReturn.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTReturn.h"
#include "SymbolTable.h"

extern void add_int_command(string);
using namespace std;

ASTReturn::ASTReturn(ASTNode *node)
{
    lchild = node;
}

string ASTReturn::getClass()
{
    return string("ASTReturn");
}

string ASTReturn::getName()
{
    return this->name;
}

string ASTReturn::getType()
{
    return lchild->getType();
}

string ASTReturn::getInternalType()
{
    return lchild->getInternalType();
}

void ASTReturn::genIntCode()
{
    lchild->genIntCode();
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "val_copy s%d s%d",
                lchild->getVarNum(), symtbl_entry->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump s%d",
                symtbl_entry->return_var_num);
    add_int_command(int_command);
}

void ASTReturn::setSymTblEntry(func_node *func)
{
    this->symtbl_entry = func;
}
