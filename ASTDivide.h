/*
 *   ASTDivide.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTDIVIDE_H
#define ASTDIVIDE_H

#include "ASTNode.h"
using namespace std;

class ASTDivide : public ASTNode
{
    public:
        ASTDivide(ASTNode *node1, ASTNode *node2);
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

#endif /* ASTDIVIDE_H */
