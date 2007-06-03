/*
 *  Assembler.cpp
 *  CSE450 Project
 *  Adam Jensen (jensena8@cse.msu.edu)
 *  Ronald Nussbaum (nussbau3@cse.msu.edu)
 */ 

#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

using namespace std;

vector<string>  tokenize_string(const string);
//
// Sizes of common items
//

// Variable name length
#define SYMSIZE 1024

// Intermediate code length
#define MAXCMDLENGTH 2048

// Debugging flags
//#define DEBUG_ASSEMBLER
//#define DEBUG

#endif /* COMMON_H */
