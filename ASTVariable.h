/*
 *   ASTVariable.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTVARIABLE_H
#define ASTVARIABLE_H

#include <fstream>
#include <iostream>
#include <string>
#include "ASTNode.h"
#include "SymbolTable.h"
using namespace std;

class ASTVariable : public ASTNode
{
    public:
        ASTVariable(string name, st_node * symtbl_entry);
        string getClass();
        string getType();
        string getInternalType();
        string getName();
        void genIntCode();
        int getValue();

    private:
        string name;
        st_node *symtbl_entry;
};

#endif /* ASTVARIABLE_H */
