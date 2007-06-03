/*
 *   ASTIf.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTIf.h"
using namespace std;

extern unsigned int var_count, label_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTIf::ASTIf(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != "scalar" || node1->getInternalType() != "number")
    {
        yyerror("Invalid conditional statement in 'if'");
    }

    this->lchild = node1;
    this->rchild = node2;
}

string ASTIf::getType()
{
    return "<ASTIf>";
}

int ASTIf::getValue()
{
}

void ASTIf::genIntCode()
{
    int lc = label_count++;

    lchild->genIntCode();
    
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "if_equ s%d 0", lchild->getVarNum());
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump if_%d", lc);
    add_int_command(int_command);

    rchild->genIntCode();

    snprintf(int_command, MAXCMDLENGTH, "if_%d:", lc);
    add_int_command(int_command);
}
