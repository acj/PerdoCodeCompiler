/*
 *   ASTFunction.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef ASTFUNCTION_H
#define ASTFUNCTION_H

#include "ASTBlock.h"
#include "ASTNode.h"
#include "SymbolTable.h"
using namespace std;

class ASTFunction : public ASTNode
{
    public:
        ASTFunction(char *, ASTNode *, ASTNode *, func_node *);
        string  getClass();
        string  getType();
        string  getInternalType();
        int     getReturnVarNum();
        void    genIntCode();
        void    setFunctionBody(ASTBlock *);
        ASTNode * leftChild();
        ASTNode * rightChild();

    private:
        ASTNode     *lchild;
        ASTNode     *rchild;
        func_node   *symtbl_entry;
        string      name;
};

#endif /* ASTFUNCTION_H */
