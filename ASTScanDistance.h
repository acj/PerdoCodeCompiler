/*
 *   ASTScanDistance.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTSCANDISTANCE_H
#define ASTSCANDISTANCE_H

#include "ASTNode.h"
using namespace std;

class ASTScanDistance : public ASTNode
{
    public:
        ASTScanDistance();
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

#endif /* ASTSCANDISTANCE_H */
