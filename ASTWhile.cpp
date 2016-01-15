/*
 *   ASTWhile.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTWhile.h"
using namespace std;

extern unsigned int var_count, label_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTWhile::ASTWhile(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != "scalar" || node1->getInternalType() != "number")
    {
        yyerror("Invalid conditional expression in 'while'");
    }

    this->lchild = node1;
    this->rchild = node2;
}

string ASTWhile::getType()
{
    return "<ASTWhile>";
}

int ASTWhile::getValue()
{
}

void ASTWhile::genIntCode()
{
    int lc = label_count++;

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "ws_%d:", lc);
    add_int_command(int_command);

    lchild->genIntCode();

    snprintf(int_command, MAXCMDLENGTH, "if_equ s%d 0", lchild->getVarNum());
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump we_%d", lc);
    add_int_command(int_command);

    rchild->genIntCode();

    snprintf(int_command, MAXCMDLENGTH, "jump ws_%d", lc);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "we_%d:", lc);
    add_int_command(int_command);
}
