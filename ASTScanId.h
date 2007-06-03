/*
 *   ASTScanId.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTSCANID_H
#define ASTSCANID_H

#include "ASTNode.h"
using namespace std;

class ASTScanId : public ASTNode
{
    public:
        ASTScanId();
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

#endif /* ASTSCANID_H */
