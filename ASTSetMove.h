/*
 *   ASTSetMove.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTSETMOVE_H
#define ASTSETMOVE_H

#include "ASTNode.h"
using namespace std;

class ASTSetMove : public ASTNode
{
    public:
        ASTSetMove(ASTNode *node1);
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

#endif /* ASTSETMOVE_H */
