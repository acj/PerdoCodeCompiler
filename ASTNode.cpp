/*
 *   ASTNode.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTNode.h"
using namespace std;

ASTNode::ASTNode()
{
    lchild = NULL;
    rchild = NULL;
    schild = NULL;
}

string ASTNode::getClass()
{
    return "ASTNode";
}

string ASTNode::getType()
{
    return "<ASTNode>";
}

string ASTNode::getInternalType()
{
    return "<ASTNodeInternal>";
}

void ASTNode::genIntCode()
{
    cerr << "genIntCode() called on undifferentiated ASTNode" << endl;
}

int ASTNode::getValue()
{
    cerr << "getValue() called on undifferentiated ASTNode" << endl;
    return 0;
}

bool ASTNode::getLvalue()
{
    return false;
}

char ASTNode::getCharValue()
{
    cerr << "getCharValue() called on undifferentiated ASTNode" << endl;
    return 0;
}

string ASTNode::getStringValue()
{
    cerr << "getStringValue() called on undifferentiated ASTNode" << endl;
    return 0;
}

ASTNode* ASTNode::leftChild()
{
    return this->lchild;
}

ASTNode* ASTNode::rightChild()
{
    return this->rchild;
}

unsigned int ASTNode::getVarNum()
{
    return this->var_num;
}

unsigned int ASTNode::getArrayVarNum()
{
}

unsigned int ASTNode::getIndexVarNum()
{
}
