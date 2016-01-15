/*
 *   ASTString.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTSTRING_H
#define ASTSTRING_H

#include "ASTNode.h"
#include "SymbolTable.h"
using namespace std;

class ASTString : public ASTNode
{
    public:
        ASTString(string value, st_node *);
        string getType();
        string getInternalType();
        void genIntCode();
        int getValue();
        string getStringValue();
        ASTNode* leftChild();
        ASTNode* rightChild();

    private:
        ASTNode* lchild;
        ASTNode* rchild;
        string value;
};

#endif /* ASTSTRING_H */
