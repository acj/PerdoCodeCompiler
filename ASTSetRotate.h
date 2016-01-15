/*
 *   ASTSetRotate.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTSETROTATE_H
#define ASTSETROTATE_H

#include "ASTNode.h"
using namespace std;

class ASTSetRotate : public ASTNode
{
    public:
        ASTSetRotate(ASTNode *node1);
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

#endif /* ASTSETROTATE_H */
