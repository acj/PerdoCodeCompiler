/*
 *   ASTOr.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTOR_H
#define ASTOR_H

#include "ASTNode.h"
using namespace std;

class ASTOr : public ASTNode
{
    public:
        ASTOr(ASTNode *node1, ASTNode *node2);
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

#endif /* ASTOr_H */
