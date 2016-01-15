/*
 *   ASTGetRotate.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTGETROTATE_H
#define ASTGETROTATE_H

#include "ASTNode.h"
using namespace std;

class ASTGetRotate : public ASTNode
{
    public:
        ASTGetRotate();
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

#endif /* ASTGETROTATE_H */
