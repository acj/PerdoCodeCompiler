/*
 *   ASTFunction.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTFunction.h"
#include "ASTReturn.h"
#include "SymbolTable.h"
using namespace std;

extern unsigned int var_count, label_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTFunction::ASTFunction(char *name,
                        ASTNode *params, 
                        ASTNode *block, 
                        func_node *sym)
{
    this->name = string(name);
    this->lchild = params;
    this->rchild = block;
    this->symtbl_entry = sym;
    
    symtbl_entry->var_num = var_count++; // Used for return value
    symtbl_entry->return_var_num = var_count++; // Used for return jump position

    if (block == NULL)
    {
        // We have a function declaration only
    }
    else if (block->getClass() != "ASTBlock")
    {
        // Handle single-statement function blocks
        if (block->getClass() == "ASTReturn")
        {
            if (block->getType() != sym->type
                || block->getInternalType() != sym->internal_type)
            {
#ifdef DEBUG
                cerr << block->getType() << "("
                        << block->getInternalType()
                        << ")" << endl;
                cerr << sym->type << "(" << sym->internal_type << ")" << endl;
#endif

                yyerror("Return type mismatch in function", name); 
            }
        }
        else
        {
            yyerror("Single statement in function body must be a return", name);
        }
    }
}

string ASTFunction::getClass()
{
    return string("ASTFunction");
}

string ASTFunction::getInternalType()
{
    return this->symtbl_entry->internal_type;
}

string ASTFunction::getType()
{
    return this->symtbl_entry->type;
}

int ASTFunction::getReturnVarNum()
{
    return this->symtbl_entry->return_var_num;
}

void ASTFunction::genIntCode()
{
    // First, verify that we have a function definition.
    if (this->rchild == NULL)
        yyerror("Function is never defined", strdup(this->name.c_str()));

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "_%s:", this->name.c_str());
    add_int_command(int_command);

    // There may not be any parameters to handle
    if (lchild != NULL)
        lchild->genIntCode();

    rchild->genIntCode();

    snprintf(int_command, MAXCMDLENGTH, "jump s%d",
                this->symtbl_entry->return_var_num);
    add_int_command(int_command);
}

void ASTFunction::setFunctionBody(ASTBlock *block)
{
    this->rchild = block;
}

ASTNode * ASTFunction::leftChild()
{
    return this->lchild;
}

ASTNode * ASTFunction::rightChild()
{
    return this->rchild;
}
