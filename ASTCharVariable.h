/*
 *   ASTCharVariable.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTCHARVARIABLE_H
#define ASTCHARVARIABLE_H

#include <fstream>
#include <iostream>
#include <string>
#include "ASTNode.h"
#include "SymbolTable.h"
using namespace std;

class ASTCharVariable : public ASTNode
{
    public:
        ASTCharVariable(string name, st_node * symtbl_entry);
        virtual string getClass();
        string getType();
        string getInternalType();
        string getName();
        void genIntCode();
        int getValue();

    private:
        string name;
        st_node *symtbl_entry;
};

#endif /* ASTCHARVARIABLE_H */
