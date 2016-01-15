/*
 *   ASTFunctionCall.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTFUNCTIONCALL_H
#define ASTFUNCTIONCALL_H

#include <fstream>
#include <iostream>
#include <string>
#include "ASTBlock.h"
#include "ASTFunction.h"
#include "ASTNode.h"
#include "SymbolTable.h"
using namespace std;

class ASTFunctionCall : public ASTNode
{
    public:
        ASTFunctionCall(char *, ASTBlock *, ASTFunction *);
        string getType();
        string getInternalType();
        string getName();
        int getVarNum();
        void genIntCode();

    private:
        ASTNode *lchild;
        string name;
        func_node *symtbl_entry;
        ASTBlock *assigns;
        ASTFunction *fptr;
};

#endif /* ASTFUNCTIONCALL_H */
