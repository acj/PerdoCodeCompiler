/*
 *   ASTIfElse.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTIfElse.h"
using namespace std;

extern unsigned int var_count, label_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTIfElse::ASTIfElse(ASTNode *node1, ASTNode *node2, ASTNode *node3)
{
    if (node1->getType() != "scalar" || node1->getInternalType() != "number")
    {
        yyerror("Invalid conditional statement in 'if-else'");
    }

    this->lchild = node1;
    this->rchild = node2;
    this->schild = node3;
}

string ASTIfElse::getType()
{
    return "<ASTIfElse>";
}

int ASTIfElse::getValue()
{
}

void ASTIfElse::genIntCode()
{
    int lc = label_count++;

    lchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "if_equ s%d 0", lchild->getVarNum());
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump if_else_%d", lc);
    add_int_command(int_command);

    rchild->genIntCode();

    snprintf(int_command, MAXCMDLENGTH, "jump if_end_%d", lc);
    add_int_command(int_command);
    
    snprintf(int_command, MAXCMDLENGTH, "if_else_%d:", lc);
    add_int_command(int_command);

    schild->genIntCode();

    snprintf(int_command, MAXCMDLENGTH, "if_end_%d:", lc);
    add_int_command(int_command);
}

ASTNode* ASTIfElse::sChild()
{
    return this->schild;
}

