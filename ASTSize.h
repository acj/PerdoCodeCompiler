/*
 *   ASTSize.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTSIZE_H
#define ASTSIZE_H

#include "ASTNode.h"
using namespace std;

class ASTSize : public ASTNode
{
    public:
        ASTSize(ASTNode *node1);
        string getType();
        string getInternalType();
        void genIntCode();
        int getValue();
        ASTNode *leftChild();
        ASTNode *rightChild();

    private:
        ASTNode *lchild;
        ASTNode *rchild;
        int value;
};

#endif /* ASTSIZE_H */
