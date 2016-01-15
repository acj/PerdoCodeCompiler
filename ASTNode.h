/*
 *   ASTNode.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTNODE_H
#define ASTNODE_H

#include <fstream>
#include <iostream>
#include <string>

#include "common.h"
using namespace std;

class ASTNode
{
    public:
        ASTNode();
        virtual string getClass();
        virtual string getType();
        virtual string getInternalType();
        virtual void genIntCode();
        virtual int getValue();
        virtual bool getLvalue();
        virtual char getCharValue();
        virtual string getStringValue();
        virtual unsigned int getArrayVarNum();
        virtual unsigned int getIndexVarNum();
        ASTNode *leftChild();
        ASTNode *rightChild();
        ASTNode *sChild();
        unsigned int getVarNum();
        unsigned int var_num;

    private:
        ASTNode *lchild;
        ASTNode *rchild;
        ASTNode *schild;
};

#endif /* ASTNODE_H */
