/*
 *   ASTZeros.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTZEROS_H
#define ASTZEROS_H

#include "ASTNode.h"
using namespace std;

class ASTZeros : public ASTNode
{
    public:
        ASTZeros(ASTNode *);
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

#endif /* ASTZEROS_H */
