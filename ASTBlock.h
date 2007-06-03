/*
 *   ASTBlock.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTBLOCK_H
#define ASTBLOCK_H

#include <vector>
#include "ASTNode.h"
using namespace std;

class ASTBlock : public ASTNode
{
    public:
        ASTBlock();
        string getClass();
        string getType();
        void genIntCode();
        ASTNode* getChild(int);
        ASTNode* getLastChild();
        int getSize();
        ASTNode* leftChild();
        ASTNode* rightChild();
        void addChild(ASTNode *);

    private:
        vector<ASTNode *> children;
        int value;
};

#endif /* ASTBLOCK_H */
