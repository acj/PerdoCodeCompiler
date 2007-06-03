/*
 *   ASTReturn.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTRETURN_H
#define ASTRETURN_H

#include <fstream>
#include <iostream>
#include <string>
#include "ASTNode.h"
#include "SymbolTable.h"
using namespace std;

class ASTReturn : public ASTNode
{
    public:
        ASTReturn(ASTNode *);
        string getClass();
        string getType();
        string getInternalType();
        string getName();
        void genIntCode();
        void setSymTblEntry(func_node *);

    private:
        ASTNode *lchild;
        string name;
        func_node *symtbl_entry;
};

#endif /* ASTRETURN_H */
