/*
 *   ASTScanId.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTScanId.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTScanId::ASTScanId()
{
    this->lchild = NULL;
    this->rchild = NULL;
    this->var_num = var_count + 1;
    var_count += 3;
}

string ASTScanId::getType()
{
    return "scalar";
}

string ASTScanId::getInternalType()
{
    return "number";
}

void ASTScanId::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "scan s%d s%d s%d", this->var_num - 1,
             this->var_num, this->var_num + 1);
    add_int_command(int_command);
}

int ASTScanId::getValue()
{
    return value;
}

ASTNode* ASTScanId::leftChild()
{
    cerr << "leftChild() called on ASTScanId node" << endl;
    return 0;
}

ASTNode* ASTScanId::rightChild()
{
    cerr << "rightChild() called on ASTScanId node" << endl;
    return 0;
}
