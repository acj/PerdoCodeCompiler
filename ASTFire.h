/*
 *   ASTFire.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTFIRE_H
#define ASTFIRE_H

#include "ASTNode.h"
using namespace std;

class ASTFire : public ASTNode
{
    public:
        ASTFire(ASTNode *node1);
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

#endif /* ASTFIRE_H */
