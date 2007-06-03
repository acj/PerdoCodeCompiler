/*
 *   ASTZeros.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTZeros.h"
using namespace std;

extern unsigned int var_count;
extern unsigned int label_count;
extern void add_int_command(string);
extern void yyerror(char *, char *detail="");

ASTZeros::ASTZeros(ASTNode *node1)
{
    if (node1->getType() != "scalar" || node1->getInternalType() != "number")
    {
        yyerror("Invalid argument to 'zeros'");
    }

    this->var_num = var_count++;
    //this->var_num = node1->getVarNum();
    lchild = node1;
}

string ASTZeros::getType()
{
    return "array";
}

string ASTZeros::getInternalType()
{
    return "number";
}

void ASTZeros::genIntCode()
{
    lchild->genIntCode(); 

    int size_register = var_count++;
    int pos_register = var_count++;
    int label_register = label_count++;

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "val_copy s%d s%d",
                this->lchild->getVarNum(), size_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "array_set_size a%d s%d",
                this->var_num, size_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "val_copy 0 s%d", pos_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "array_zeros_start_%d:",
                label_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "if_equ s%d s%d",
                pos_register, size_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump array_zeros_end_%d",
                label_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "array_set_index a%d s%d 0",
                this->var_num, pos_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "add s%d 1 s%d", 
                pos_register, pos_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "jump array_zeros_start_%d",
                label_register);
    add_int_command(int_command);

    snprintf(int_command, MAXCMDLENGTH, "array_zeros_end_%d:",
                label_register);
    add_int_command(int_command);
}

int ASTZeros::getValue()
{
    return value;
}

ASTNode* ASTZeros::leftChild()
{
    cerr << "leftChild() called on ASTZeros node" << endl;
    return 0;
}

ASTNode* ASTZeros::rightChild()
{
    cerr << "rightChild() called on ASTZeros node" << endl;
    return 0;
}
