/*
 *   ASTChar.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTCHAR_H
#define ASTCHAR_H

#include "ASTNode.h"
using namespace std;

class ASTChar : public ASTNode
{
    public:
        ASTChar(char value);
        string getClass();
        string getType();
        string getInternalType();
        void genIntCode();
        int getValue();
        char getCharValue();
        ASTNode* leftChild();
        ASTNode* rightChild();

    private:
        ASTNode* lchild;
        ASTNode* rchild;
        char value;
};

#endif /* ASTCHAR_H */
