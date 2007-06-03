/*
 *   ASTRandom.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTRANDOM_H
#define ASTRANDOM_H

#include "ASTNode.h"
using namespace std;

class ASTRandom : public ASTNode
{
    public:
        ASTRandom(ASTNode *node1);
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

#endif /* ASTRANDOM_H */
