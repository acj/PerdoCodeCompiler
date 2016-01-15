/*
 *   ASTValue.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTVALUE_H
#define ASTVALUE_H

#include "ASTNode.h"
using namespace std;

class ASTValue : public ASTNode
{
    public:
        ASTValue(int value);
        string getClass();
        string getType();
        string getInternalType();
        void genIntCode();
        int getValue();
        ASTNode* leftChild();
        ASTNode* rightChild();

    private:
        ASTNode* lchild;
        ASTNode* rchild;
        int value;
};

#endif /* ASTVALUE_H */
