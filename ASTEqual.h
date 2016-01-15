/*
 *   ASTEqual.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTEQUAL_H
#define ASTEQUAL_H

#include "ASTNode.h"
using namespace std;

class ASTEqual : public ASTNode
{
    public:
        ASTEqual(ASTNode *node1, ASTNode *node2);
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

#endif /* ASTEQUAL_H */
