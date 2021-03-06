/*
 *   ASTGetShields.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTGETSHIELDS_H
#define ASTGETSHIELDS_H

#include "ASTNode.h"
using namespace std;

class ASTGetShields : public ASTNode
{
    public:
        ASTGetShields();
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

#endif /* ASTGETSHIELDS_H */
