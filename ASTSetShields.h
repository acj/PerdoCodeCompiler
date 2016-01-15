/*
 *   ASTSetShields.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTSETSHIELDS_H
#define ASTSETSHIELDS_H

#include "ASTNode.h"
using namespace std;

class ASTSetShields : public ASTNode
{
    public:
        ASTSetShields(ASTNode *node1);
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

#endif /* ASTSETSHIELDS_H */
