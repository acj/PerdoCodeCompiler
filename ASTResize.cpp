/*
 *   ASTResize.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTResize.h"
#include "ASTArray.h"
using namespace std;

extern unsigned int var_count;
extern void yyerror(char *error_string, char *detail="");
extern void add_int_command(string);

ASTResize::ASTResize(ASTArray *node1, ASTNode *node2)
{
    if (node1->getType() != "array" 
        || node2->getType() != "scalar"
        || node2->getInternalType() != "number")
    {
        yyerror("Invalid argument type");
    }

    lchild = node1;
    rchild = node2;
}

string ASTResize::getType()
{
    return "<ASTResize>";
}

void ASTResize::genIntCode()
{
    lchild->genIntCode();
    rchild->genIntCode();

    char int_command[MAXCMDLENGTH];

    snprintf(int_command, MAXCMDLENGTH, "array_set_size a%d s%d",
                lchild->getVarNum(), rchild->getVarNum());
    add_int_command(int_command);
}

int ASTResize::getValue()
{
}

ASTNode* ASTResize::leftChild()
{
    cerr << "leftChild() called on ASTResize node" << endl;
    return 0;
}

ASTNode* ASTResize::rightChild()
{
    cerr << "rightChild() called on ASTResize node" << endl;
    return 0;
}
