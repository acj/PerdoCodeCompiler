/*
 *   ASTBlock.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include <vector>
#include "ASTBlock.h"
using namespace std;

extern unsigned int var_count;
extern void add_int_command(string);
extern ofstream pciout;

ASTBlock::ASTBlock()
{
}

string ASTBlock::getClass()
{
    return string("ASTBlock");
}

string ASTBlock::getType()
{
    return "<ASTBlock>";
}

void ASTBlock::genIntCode()
{
    vector<ASTNode *>::const_iterator child_iter;
    
    for (child_iter = this->children.begin(); 
        child_iter != this->children.end(); 
        child_iter++)
        (*child_iter)->genIntCode();
}

ASTNode* ASTBlock::getChild(int index)
{
    if (index >= 0 && index < children.size())
        return this->children[index];
}

ASTNode* ASTBlock::getLastChild()
{
    if (this->children.size() == 0)
    {
        cerr << "ASTBlock: Last child requested, but no children!" << endl;
        return 0;
    }

    return children[this->children.size()-1];
}

int ASTBlock::getSize()
{
    return this->children.size();
}

ASTNode* ASTBlock::leftChild()
{
    cerr << "leftchild() called on ASTBlock node" << endl;
}

ASTNode* ASTBlock::rightChild()
{
    cerr << "rightChild() called on ASTBlock node" << endl;
}

void ASTBlock::addChild(ASTNode *new_node)
{
    if (new_node == NULL)
        cerr << "ASTBlock::addChild(): Null pointer detected" << endl;
    else
        this->children.push_back(new_node);
}
