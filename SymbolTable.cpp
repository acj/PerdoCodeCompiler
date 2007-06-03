/*
 *   SymbolTable.cpp
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

#include "common.h"
#include "SymbolTable.h"
using namespace std;

extern unsigned int current_scope;
extern bool function_context;

static map<string, st_node *> sym_tab;
static map<string, func_node *> func_tab;
static string current_function;

func_node * func_add(char *func_name, char *type, char *internal_type="")
{
    string str_func_name = string(func_name);

    if (func_tab.find(str_func_name) != func_tab.end())
    {
        func_node *entry = func_tab[str_func_name];
        entry->name = func_name;
        entry->declared = true;
        entry->type = type;
        entry->internal_type = internal_type;
        return entry;
    }
    else
    {
        func_node *entry = new func_node;
        func_tab[str_func_name] = entry;
        entry->name = func_name;
        entry->declared = true;
        entry->type = type;
        entry->internal_type = internal_type;
        return entry;
    }
}

st_node * sym_add(char *sym_name, char *type)
{
    char s[SYMSIZE];

    if (function_context)
        sprintf(s, "function_%s_%d\\", current_function.c_str(), current_scope);
    else
        sprintf(s, "%d\\", current_scope);

    string scope_encoded_name = string(s) + string(sym_name);

#ifdef DEBUG
    cerr << "Adding symbol: " << s + string(sym_name) << endl;
#endif

    if (sym_tab.find(scope_encoded_name) != sym_tab.end() &&
        !(sym_tab[scope_encoded_name]->active))
    {
        st_node *entry = sym_tab[scope_encoded_name];
        entry->name = scope_encoded_name;
        entry->active = true;
        entry->init = false;
        entry->type = string(type);
        return entry;
    }
    else
    {
        st_node *new_entry = new st_node;
        sym_tab[scope_encoded_name] = new_entry;
        new_entry->name = scope_encoded_name;
        new_entry->active = true;
        new_entry->init = false;
        new_entry->scope = current_scope;
        new_entry->type = string(type);
        return new_entry; 
    }
}

func_node * func_get(char *func_name)
{
    if (func_tab.find(string(func_name)) != func_tab.end())
        return func_tab[func_name];
    else
        return NULL;
}

char * sym_get_current_function()
{
    return strdup(current_function.c_str());
}

void sym_set_current_function(char *new_function)
{
    current_function = new_function;
}

st_node * sym_get(char *sym_name)
{
    for (int i = current_scope; i >= 0; i--)
    {
        char s[SYMSIZE];

        // Prepend the scope
        if (function_context)
            sprintf(s, "function_%s_%d\\", current_function.c_str(), i);
        else
            sprintf(s, "%d\\", i);

#ifdef DEBUG
        cerr << "Looking up symbol: " << s + string(sym_name) << endl;
#endif

        // Look for the symbol
        if (sym_tab.find(string(s) + string(sym_name)) != sym_tab.end() 
            && sym_tab[string(s) + string(sym_name)]->active)
                return sym_tab[string(s) + string(sym_name)];
        else
        {
            // If we can't find the symbol in our function scope, let's
            // look at the global scope
            if (function_context)
            {
#ifdef DEBUG
        cerr << "Looking up symbol: " << s + string(sym_name) << endl;
#endif

                if (sym_tab.find("0\\" + string(sym_name)) != sym_tab.end() 
                    && sym_tab["0\\" + string(sym_name)]->active)
                return sym_tab["0\\" + string(sym_name)];
            }
        }
    }
}

bool func_exists(char *func_name)
{
    string name = string(func_name);
    if (func_tab.find(name) != func_tab.end())
        return true;
    else
        return false;
}

bool sym_exists(char *sym_name)
{
    for (int i = current_scope; i >= 0; i--)
    {
        char s[SYMSIZE];

        if (function_context)
            sprintf(s, "function_%s_%d\\", current_function.c_str(), i);
        else
            sprintf(s, "%d\\", i);

#ifdef DEBUG
        cerr << "Checking symbol existence: " << s + string(sym_name)  << endl;
#endif

        if (sym_tab.find(string(s) + string(sym_name)) != sym_tab.end() 
            && sym_tab[string(s) + string(sym_name)]->active)
                return true;
        else
        {
            // If we can't find the symbol in our function scope, let's
            // look at the global scope
            if (function_context)
            {
                sprintf(s, "0\\");

#ifdef DEBUG
                cerr << "Checking symbol existence: " 
                    << s + string(sym_name)  << endl;
#endif

                if (sym_tab.find(string(s) + string(sym_name)) != sym_tab.end() 
                    && sym_tab[string(s) + string(sym_name)]->active)
                return sym_tab[string(s) + string(sym_name)];
            }
        }
    }
    return false;
}

bool sym_init(char *sym_name, bool init = false)
{
    // Are we being asked to initialize this variable?
    if (init)
    {
        for (int i = current_scope; i >= 0; i--)
        {
            char s[SYMSIZE];
            
            if (function_context)
                sprintf(s, "function_%s_%d\\", current_function.c_str(), i);
            else
                sprintf(s, "%d\\", i);

#ifdef DEBUG
            cerr << "Initializing symbol: " << s + string(sym_name) << endl;
#endif

            if (sym_tab.find(string(s) + string(sym_name)) != sym_tab.end() 
                    && sym_tab[string(s) + string(sym_name)]->active)
            {
                sym_tab[string(s) + string(sym_name)]->init = true;
                return true;
            }
            else
            {
                // If we can't find the symbol in our function scope, let's
                // look at the global scope
                if (function_context)
                {
                    sprintf(s, "0\\");

#ifdef DEBUG
                    cerr << " Checking symbol existence: " 
                        << s + string(sym_name)  << endl;
#endif

                    if (sym_tab.find(string(s) + string(sym_name)) 
                            != sym_tab.end() 
                        && sym_tab[string(s) + string(sym_name)]->active)
                            return sym_tab[string(s) + string(sym_name)];
                }
            }
        }
    }

    // Otherwise, check to see if the variable is initialized
    for (int i = current_scope; i >= 0; i--)
    {
        char s[SYMSIZE];
        
        if (function_context)
            sprintf(s, "function_%s_%d\\", current_function.c_str(), i);
        else
            sprintf(s, "%d\\", i);

        if (sym_tab.find(string(s) + string(sym_name)) != sym_tab.end() 
            && sym_tab[string(s) + string(sym_name)]->active
            && sym_tab[string(s) + string(sym_name)]->init)
        {
            return true;
        }
        else
        {
            // If we can't find the symbol in our function scope, let's
            // look at the global scope
            if (function_context)
            {
                sprintf(s, "0\\");

#ifdef DEBUG
                    cerr << " Checking symbol existence: " 
                        << s + string(sym_name)  << endl;
#endif
                
                if (sym_tab.find(string(s) + string(sym_name)) != sym_tab.end() 
                    && sym_tab[string(s) + string(sym_name)]->active)
                        return sym_tab[string(s) + string(sym_name)];
            }
        }
    }
    return false;
}

void sym_deactivate()
{
    map<string, st_node *>::iterator iter;
    for (iter = sym_tab.begin(); iter != sym_tab.end(); iter++)
    {
        if (iter->second->scope > current_scope)
        {
            iter->second->active = false;

#ifdef DEBUG
            cerr << "Passing out of scope: " << iter->second->name << endl;
#endif
        }
    }
}

// Return a list of variable numbers associated with arrays
vector<int> sym_get_arrays()
{
    vector<int> arrays;

    map<string, st_node *>::const_iterator iter;
    for (iter = sym_tab.begin(); iter != sym_tab.end(); iter++)
    {
        if (iter->second->type == "array")
            arrays.push_back(iter->second->var_num);
    }

    return arrays;
}
