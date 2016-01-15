/*
 *   ASTResize.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTRESIZE_H
#define ASTRESIZE_H

#include "ASTNode.h"
#include "ASTArray.h"
using namespace std;

class ASTResize : public ASTNode
{
    public:
        ASTResize(ASTArray *, ASTNode *);
        string getType();
        void genIntCode();
        int getValue();
        ASTNode* leftChild();
        ASTNode* rightChild();

    private:
        ASTNode* lchild;
        ASTNode* rchild;
        int value;
};

#endif /* ASTRESIZE_H */
