/*
 *   ASTArray.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTARRAY_H
#define ASTARRAY_H

#include "ASTNode.h"
#include "SymbolTable.h"
using namespace std;

class ASTArray : public ASTNode
{
    public:
        ASTArray(string, st_node *);
        string  getType();
        string  getInternalType();
        void    setInternalType(string);
        void    genIntCode();
        bool    getLvalue();
        void    setLvalue(bool);
        int     getValue();
        ASTNode* leftChild();
        ASTNode* rightChild();

    private:
        ASTNode    *lchild;
        ASTNode    *rchild;
        string      name;
        st_node    *symtbl_entry;
        bool        lvalue;
};

#endif /* ASTARRAY_H */
