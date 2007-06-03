/*
 *   ASTScanDistance.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTScanDistance.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTScanDistance::ASTScanDistance()
{
    this->lchild = NULL;
    this->rchild = NULL;
    this->var_num = var_count;
    var_count += 3;
}

string ASTScanDistance::getType()
{
    return "scalar";
}

string ASTScanDistance::getInternalType()
{
    return "number";
}

void ASTScanDistance::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "scan s%d s%d s%d", this->var_num,
             this->var_num + 1, this->var_num + 2);
    add_int_command(int_command);
}

int ASTScanDistance::getValue()
{
    return value;
}

ASTNode* ASTScanDistance::leftChild()
{
    cerr << "leftChild() called on ASTScanDistance node" << endl;
    return 0;
}

ASTNode* ASTScanDistance::rightChild()
{
    cerr << "rightChild() called on ASTScanDistance node" << endl;
    return 0;
}
