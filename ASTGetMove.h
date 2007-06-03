/*
 *   ASTGetMove.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTGETMOVE_H
#define ASTGETMOVE_H

#include "ASTNode.h"
using namespace std;

class ASTGetMove : public ASTNode
{
    public:
        ASTGetMove();
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

#endif /* ASTGETMOVE_H */
