/*
 *   ASTScanAngle.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTScanAngle.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);

ASTScanAngle::ASTScanAngle()
{
    this->lchild = NULL;
    this->rchild = NULL;
    this->var_num = var_count + 2;
    var_count += 3;
}

string ASTScanAngle::getType()
{
    return "scalar";
}

string ASTScanAngle::getInternalType()
{
    return "number";
}

void ASTScanAngle::genIntCode()
{
    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "scan s%d s%d s%d", this->var_num - 2,
             this->var_num - 1, this->var_num);
    add_int_command(int_command);
}

int ASTScanAngle::getValue()
{
    return value;
}

ASTNode* ASTScanAngle::leftChild()
{
    cerr << "leftChild() called on ASTScanAngle node" << endl;
    return 0;
}

ASTNode* ASTScanAngle::rightChild()
{
    cerr << "rightChild() called on ASTScanAngle node" << endl;
    return 0;
}
