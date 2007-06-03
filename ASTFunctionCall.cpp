/*
 *   ASTFunctionCall.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTAssignment.h"
#include "ASTBlock.h"
#include "ASTFunctionCall.h"
#include "ASTFunction.h"
#include "SymbolTable.h"

extern int label_count, var_count;
extern void add_int_command(string);
extern void yyerror(char *, char *details="");
using namespace std;

ASTFunctionCall::ASTFunctionCall(char *name, ASTBlock *args, ASTFunction *fptr)
{
    lchild = args;
    func_node *symtbl_entry = func_get(name);
    this->symtbl_entry = symtbl_entry;
    this->var_num = var_count++;
    this->fptr = fptr;

    ASTBlock *fparams = (ASTBlock *)fptr->leftChild();

    // Check the number of arguments (if there are any)
    int args_count = 0;

    if (args != NULL)
        args_count = args->getSize();

    if (fparams->getSize() != args_count)
    {
        yyerror("Incorrect number of arguments to function", 
                strdup(name));
    }
    
    // Set up a series of assignments that map the input arguments to the
    // function's formal parameters.
    this->assigns = new ASTBlock();

    if (args_count > 0)
    {
        int count = fparams->getSize();
        int index;
        for (index=0; index<count; ++index)
        {
            this->assigns->addChild(new ASTAssignment(fparams->getChild(index), 
                                args->getChild(index)));
        }
    }
}

string ASTFunctionCall::getName()
{
}

string ASTFunctionCall::getType()
{
    return this->symtbl_entry->type;
}

string ASTFunctionCall::getInternalType()
{
    return this->symtbl_entry->internal_type;
}

int ASTFunctionCall::getVarNum()
{
    return this->var_num;
}

void ASTFunctionCall::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    // FIXME: Drop a "function_return_X" label.  Before the label, copy the
    // label's value to the target function's "return pos" variable.  Jump.

    int label_num = label_count++;

    assigns->genIntCode();
    snprintf(int_command, MAXCMDLENGTH, "val_copy _function_return_%d s%d",
                label_num, this->symtbl_entry->return_var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump _%s", 
                strdup(this->symtbl_entry->name.c_str()));
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "_function_return_%d:",
                label_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "val_copy s%d s%d",
                    this->symtbl_entry->var_num, this->var_num); 
    add_int_command(int_command);
}
