#ifndef ASTASSIGNMENT_H
#define ASTASSIGNMENT_H

#include "ASTArray.h"
#include "ASTArrayIndex.h"
#include "ASTNode.h"
#include "ASTCharVariable.h"
#include "ASTVariable.h"
using namespace std;

class ASTAssignment : public ASTNode
{
    public:
        ASTAssignment(ASTNode *, ASTNode *);
        ASTAssignment(ASTArrayIndex *, ASTNode *, ASTNode *);
        string getClass();
        void genIntCode();
        int getValue();
        ASTNode *leftChild();
        ASTNode *rightChild();

    private:
        ASTNode *lchild;
        ASTNode *rchild;
        ASTNode *schild;
};

#endif /* ASTASSIGNMENT_H */
