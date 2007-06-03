/*
 *   ASTArrayIndex.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTArrayIndex.h"
#include <string>
using namespace std;

extern unsigned int var_count;
extern void yyerror(char *error_string, char *detail="");
extern void add_int_command(string);

ASTArrayIndex::ASTArrayIndex(
                string name, 
                ASTNode *index, 
                bool lvalue,
                st_node *symtbl_entry)
{
    this->name = name;
    this->symtbl_entry = symtbl_entry;
    this->index = index;
    this->lvalue = lvalue;

    if (!lvalue)
    {
        this->var_num = var_count++;
    }

    if (index->getType() != "scalar")
    {
        yyerror("Invalid array index type");
    }

    this->lchild = index;
    this->rchild = NULL;
}

unsigned int ASTArrayIndex::getArrayVarNum()
{
    return this->symtbl_entry->var_num;
}

unsigned int ASTArrayIndex::getIndexVarNum()
{
    return this->rchild->getVarNum();
}

string ASTArrayIndex::getType()
{
    return "scalar";
}

string ASTArrayIndex::getInternalType()
{
    return symtbl_entry->internal_type;
}

void ASTArrayIndex::setInternalType(string new_type)
{
}

bool ASTArrayIndex::getLvalue()
{
    return this->lvalue;
}

void ASTArrayIndex::setLvalue(bool new_value)
{
    this->lvalue = new_value;
}

void ASTArrayIndex::genIntCode()
{
    lchild->genIntCode();

    if (!this->getLvalue())
    {
        // We're getting an element in the array
        lchild->genIntCode();
        index->genIntCode();

        char int_command[MAXCMDLENGTH];

        snprintf(int_command, MAXCMDLENGTH, "array_get_index a%d s%d s%d",
                    symtbl_entry->var_num, index->getVarNum(), this->var_num);
        add_int_command(int_command);
    }
}

int ASTArrayIndex::getValue()
{
}

ASTNode* ASTArrayIndex::leftChild()
{
    cerr << "leftChild() called on ASTArrayIndex node" << endl;
    return 0;
}

ASTNode* ASTArrayIndex::rightChild()
{
    cerr << "rightChild() called on ASTArrayIndex node" << endl;
    return 0;
}
