/*
 *   ASTScanAngle.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTSCANANGLE_H
#define ASTSCANANGLE_H

#include "ASTNode.h"
using namespace std;

class ASTScanAngle : public ASTNode
{
    public:
        ASTScanAngle();
        string getType();
        void genIntCode();
        string getInternalType();
        int getValue();
        ASTNode* leftChild();
        ASTNode* rightChild();

    private:
        ASTNode* lchild;
        ASTNode* rchild;
        int value;
};

#endif /* ASTSCANANGLE_H */
