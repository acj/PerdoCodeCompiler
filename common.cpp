#include <string>
#include <vector>
#include "ASTBlock.h"
using namespace std;

/* True if the argument is whitespace, false otherwise */
bool space(char c) { return isspace(c); }

/* False if the argument is whitespace, true otherwise */
bool not_space(char c) { return !isspace(c); }

vector<string> tokenize_string(const string str)
{
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();
    while (i != str.end())
    {
        /* Ignore leading blanks */
        i = find_if(i, str.end(), not_space);
        /* Find end of next word */
        iter j = find_if(i, str.end(), space);
        /* Copy the characters in [i, j) */
        if (i != str.end()) ret.push_back(string(i, j));
        i = j;
    }
    return ret;
}

