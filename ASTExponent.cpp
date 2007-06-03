/*
 *   ASTExponent.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTExponent.h"
using namespace std;

extern unsigned int var_count, label_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTExponent::ASTExponent(ASTNode *node1, ASTNode *node2)
{
    if (node1->getType() != "scalar" || node2->getType() != "scalar")
    {
        yyerror("Invalid operand to '^'");
    }

    this->lchild = node1;
    this->rchild = node2;
    this->var_num = var_count++;    
}

string ASTExponent::getType()
{
    return "scalar";
}

string ASTExponent::getInternalType()
{
    return "number";
}

void ASTExponent::genIntCode()
{
    lchild->genIntCode();
    rchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "val_copy 1 s%d", this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "val_copy s%d s1", rchild->getVarNum());
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "e_%d:", label_count);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_less s1 0");
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "div s%d s%d s%d",
                this->var_num, lchild->getVarNum(), this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_less s1 0");
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "add s1 1 s1");
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_gr s1 0");
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "mult s%d s%d s%d",
                this->var_num, lchild->getVarNum(), this->var_num);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_gtr s1 0");
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "sub s1 1 s1");
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_n_equ s1 0");
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump e_%d", label_count++);
    add_int_command(int_command);
}

int ASTExponent::getValue()
{
}
