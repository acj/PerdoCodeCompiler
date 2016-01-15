/*
 *   ASTWhile.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTWHILE_H
#define ASTWHILE_H

#include "ASTNode.h"
using namespace std;

class ASTWhile : public ASTNode
{
    public:
        ASTWhile(ASTNode *node1, ASTNode *node2);
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

#endif /* ASTWHILE_H */
