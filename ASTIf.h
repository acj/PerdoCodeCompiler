/*
 *   ASTIf.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTIF_H
#define ASTIF_H

#include "ASTNode.h"
using namespace std;

class ASTIf : public ASTNode
{
    public:
        ASTIf(ASTNode *node1, ASTNode *node2);
        string getType();
        void genIntCode();
        int getValue();
        ASTNode *leftChild();
        ASTNode *rightChild();

    private:
        ASTNode *lchild;
        ASTNode *rchild;
        int value;
};

#endif /* ASTIF_H */
