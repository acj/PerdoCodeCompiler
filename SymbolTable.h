/*
 *   SymbolTable.h
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ASTNode.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct func_node
{
    string name, type, internal_type;
    int var_num, return_var_num;
    ASTNode *func;
    bool declared;
    bool defined;
};

struct st_node
{
    string name;
    bool active, init;
    int scope, var_num, value;
    string type, internal_type;
};
typedef struct func_node func_node;
typedef struct st_node st_node;

func_node * func_add(char *, char *, char *);
st_node * sym_add(char *, char *);
func_node * func_get(char *);
char * sym_get_current_function();
void sym_set_current_function(char *);
st_node * sym_get(char *);
bool func_exists(char *);
bool sym_exists(char *);
bool sym_init(char *, bool);
void sym_deactivate();
vector<int> sym_get_arrays();
#endif /* SYMBOL_TABLE */
