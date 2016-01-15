/*
 *   ASTSize.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTSize.h"
using namespace std;

extern unsigned int var_count;
extern void yyerror(char *error_string, char *detail="");
extern void add_int_command(string);

ASTSize::ASTSize(ASTNode *node1)
{
    if (node1->getType() != "array")
    {
        yyerror("Invalid argument to size", strdup(node1->getType().c_str()));
    }

    this->lchild = node1;
    this->rchild = NULL;
    this->var_num = var_count++;
}

string ASTSize::getType()
{
    return "scalar";
}

string ASTSize::getInternalType()
{
    return "number";
}

void ASTSize::genIntCode()
{
    lchild->genIntCode();
    
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "array_get_size a%d s%d",
                lchild->getVarNum(), this->var_num);
    add_int_command(int_command);
}

int ASTSize::getValue()
{
}

