/*
 *   ASTPrint.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTPRINT_H
#define ASTPRINT_H

#include "ASTNode.h"
using namespace std;

class ASTPrint : public ASTNode
{
    public:
        ASTPrint(ASTNode *);
        string getType();
        void genIntCode();
        void setNewline(bool);
        int getValue();
        ASTNode *leftChild();
        ASTNode *rightChild();

    private:
        ASTNode *lchild;
        ASTNode *rchild;
        int value;
        bool newline;
};

#endif /* ASTPRINT_H */
