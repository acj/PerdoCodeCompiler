/*
 *   ASTArrayIndex.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTARRAYINDEX_H
#define ASTARRAYINDEX_H

#include "ASTNode.h"
#include "SymbolTable.h"
using namespace std;

class ASTArrayIndex : public ASTNode
{
    public:
        ASTArrayIndex(string, ASTNode *, bool, st_node *);
        unsigned int     getArrayVarNum();
        unsigned int     getIndexVarNum();
        string  getType();
        string  getInternalType();
        void    setInternalType(string);
        void    genIntCode();
        int     getValue();
        bool    getLvalue();
        void    setLvalue(bool);
        ASTNode* leftChild();
        ASTNode* rightChild();

    private:
        ASTNode    *lchild;
        ASTNode    *rchild;
        ASTNode    *index;
        string      name;
        bool        lvalue;
        st_node    *symtbl_entry;
};

#endif /* ASTARRAYINDEX_H */
