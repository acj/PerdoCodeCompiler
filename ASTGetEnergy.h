/*
 *   ASTGetEnergy.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTGETENERGY_H
#define ASTGETENERGY_H

#include "ASTNode.h"
using namespace std;

class ASTGetEnergy : public ASTNode
{
    public:
        ASTGetEnergy();
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

#endif /* ASTGETENERGY_H */
