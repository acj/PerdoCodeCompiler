/*
 *   ASTIfElse.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTIFELSE_H
#define ASTIFELSE_H

#include "ASTNode.h"
using namespace std;

class ASTIfElse : public ASTNode
{
    public:
        ASTIfElse(ASTNode *node1, ASTNode *node2, ASTNode *node3);
        string getType();
        void genIntCode();
        int getValue();
        ASTNode *leftChild();
        ASTNode *rightChild();
        ASTNode *sChild();

    private:
        ASTNode *lchild;
        ASTNode *rchild;
        ASTNode *schild;
        int value;
};

#endif /* ASTIFELSE_H */
