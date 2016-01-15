/*
 *   ASTUnaryMinus.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTUNARYMINUS_H
#define ASTUNARYMINUS_H

#include "ASTNode.h"
using namespace std;

class ASTUnaryMinus : public ASTNode
{
    public:
        ASTUnaryMinus(ASTNode *node1);
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

#endif /* ASTUNARYMINUS_H */
