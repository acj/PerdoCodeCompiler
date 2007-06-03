/*
 *   ASTAssignment.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "ASTAssignment.h"
using namespace std;

extern void sym_set_val(char *sym_name, int sym_value);
extern void yyerror(char *error_string, char *detail="");
extern void add_int_command(string);

ASTAssignment::ASTAssignment(ASTNode *node1, ASTNode *node2)
{
#ifdef DEBUG
    cerr << "New ASTAssignment (" << node1->getVarNum()
         << "-->" << node2->getVarNum() << "): "
         << node1->getType() << ":" << node1->getInternalType()
         << "-->" << node2->getType() << ":" << node2->getInternalType()
         << endl;
#endif

    if (node1->getType() != node2->getType()
        || node1->getInternalType() != node2->getInternalType())
    {
        yyerror("Type mismatch");
    }

    this->lchild = node1;
    this->rchild = node2;
}

ASTAssignment::ASTAssignment(
                ASTArrayIndex *array, 
                ASTNode *index, 
                ASTNode *expr)
{
    this->lchild = array;
    this->rchild = index;
    this->schild = expr;
}

string ASTAssignment::getClass()
{
    return "ASTAssignment";
}

void ASTAssignment::genIntCode()
{
    if (lchild == 0 || rchild == 0)
        cerr << "Missing at least one child" << endl;

    char int_command[MAXCMDLENGTH];

    if (lchild->getType() == "array" && rchild->getType() == "array")
    {
        rchild->genIntCode();

        // We expect "rchild" to be a literal string or another array here
        if (rchild->getType() == "array" 
            && rchild->getInternalType() == "number")
        {
            snprintf(int_command, MAXCMDLENGTH, "array_copy a%d a%d",
                        rchild->getVarNum(), lchild->getVarNum());
            add_int_command(int_command);
        }
        else if (rchild->getType() == "array" 
                && rchild->getInternalType() == "char")
        {
            lchild->genIntCode();

            snprintf(int_command, MAXCMDLENGTH, "array_copy a%d a%d",
                        rchild->getVarNum(), lchild->getVarNum());
            add_int_command(int_command);
        }
        else
        {
            // Sanity check
            cerr << "Node of type " << rchild->getType() << " passed in"
                    << " array assignment" << endl;
        }
    }
    else if (lchild->getType() == "scalar" && lchild->getLvalue())
    {
        // This is an assignment to an array index
        lchild->genIntCode();
        rchild->genIntCode();
        schild->genIntCode();

        snprintf(int_command, MAXCMDLENGTH, "array_set_index a%d s%d s%d",
                    lchild->getArrayVarNum(), rchild->getVarNum(), 
                    schild->getVarNum());
        add_int_command(int_command);
    }
    else
    {
        if (rchild->getClass() == "ASTChar")
        {
            snprintf(int_command, MAXCMDLENGTH, "val_copy '%c' s%d",
                        rchild->getCharValue(), lchild->getVarNum());
            add_int_command(int_command);
        }
        else if (rchild->getClass() == "ASTValue")
        {
            snprintf(int_command, MAXCMDLENGTH, "val_copy %d s%d",
                        rchild->getValue(), lchild->getVarNum());
            add_int_command(int_command);
        }
        else
        {
            rchild->genIntCode();

            snprintf(int_command, MAXCMDLENGTH, "val_copy s%d s%d",
                        rchild->getVarNum(), lchild->getVarNum());
            add_int_command(int_command);
        }
    }
}

int ASTAssignment::getValue()
{
}
