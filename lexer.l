/*
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

%{
    #include <iostream>
    #include "parser.tab.h"
    #include "SymbolTable.h"

    unsigned typeCount = 0, commandCount = 0, idCount = 0, numberCount = 0,
        operatorCount = 0, endlineCount = 0, commentCount = 0, lineCount = 0,
        whitespaceCount = 0, eolCount = 0, charCount = 0, unknowncharCount = 0;
    void count_eol(char *comment_string, size_t len);
    extern int symlookup(char *symname);
%}

COMMENT	        #.*
CCOMMENT        \/\*(.|\n)*\*\/
FDECLARE        "declare"
DEFINE 	        "define"
TYPE            "number"|"char"|"string"
ARRAY		"array"
COMMAND         "if"|"else"|"while"|"print"|"random"|"time"|"resize"|"size"|"zeros"
RETURN          "return"
ROBOT           "set_rotate"|"get_rotate"|"set_move"|"get_move"|"set_shields"|"get_shields"|"fire"|"get_energy"|"scan_distance"|"scan_angle"|"scan_id"
CHARLIT		\'.\'
STRLIT		\"[^\"]*\"
IDENT           [A-Za-z_][A-Za-z_0-9]*
NUMBER          [0-9]+
ENDLINE         ";"
WHITESPACE      [\t ]
EOL             \n

%%

{CCOMMENT}      {
                    count_eol(yytext, yyleng); commentCount++;
                    charCount += yyleng;
                }
{COMMENT}       { commentCount++; charCount += yyleng; }
{FDECLARE}       {
                    charCount += 7;
                    return FDECLARE;
                }
{DEFINE}        {
                    charCount += 6;
                    return DEFINE;
                }
{TYPE}          { 
		    typeCount++; 
		    charCount += yyleng; 
		    yylval.strval = strdup(yytext);
		    return TYPE; 
		}
{ARRAY}		{ 
		    charCount += yyleng; 
		    return ARRAY;
		}
{COMMAND}       {
                    commandCount++; charCount += yyleng;
                    yylval.strval = strdup(yytext);
                    if (!strcmp("if", yytext))
                        return IF;
                    else if (!strcmp("else", yytext))
                        return ELSE;
                    else if (!strcmp("while", yytext))
                        return WHILE;
                    else if (!strcmp("print", yytext))
                        return PRINT;
                    else if (!strcmp("random", yytext))
                        return RANDOM;
                    else if (!strcmp("time", yytext))
                        return TIME;
		    else if (!strcmp("size", yytext))
			return SIZE;
		    else if (!strcmp("resize", yytext))
			return RESIZE;
		    else if (!strcmp("zeros", yytext))
			return ZEROS;
		}
{RETURN}        { 
                    charCount += 6;
                    yylval.strval = "return";
                    return RETURN;
                }
{ROBOT}		{
		    charCount += yyleng;
		    yylval.strval = strdup(yytext);
		    if (!strcmp("set_rotate", yytext))
		        return SET_ROTATE;
		    else if (!strcmp("get_rotate", yytext))
		        return GET_ROTATE;
		    else if (!strcmp("set_move", yytext))
		        return SET_MOVE;
		    else if (!strcmp("get_move", yytext))
		        return GET_MOVE;
		    else if (!strcmp("set_shields", yytext))
		        return SET_SHIELDS;
		    else if (!strcmp("get_shields", yytext))
		        return GET_SHIELDS;
		    else if (!strcmp("fire", yytext))
		        return FIRE;
		    else if (!strcmp("get_energy", yytext))
		        return GET_ENERGY;
		    else if (!strcmp("scan_distance", yytext))
		        return SCAN_DISTANCE;
		    else if (!strcmp("scan_angle", yytext))
		        return SCAN_ANGLE;
		    else if (!strcmp("scan_id", yytext))
		        return SCAN_ID;
		}
{CHARLIT}	{
		    charCount += yyleng;
		    yylval.charval = yytext[1];
		    return CHARLIT;
		}
{STRLIT}	{
		    charCount += yyleng;
		    yylval.strval = strdup(yytext);
		    return STRLIT;
		}
{IDENT}         {
                    idCount++; charCount += yyleng;
                    yylval.strval = strdup(yytext);
                    return NAME;
                }
{NUMBER}        {
                    numberCount++; charCount += yyleng;
                    yylval.intval = atoi(yytext);
                    return NUMBER;
                }
{ENDLINE}       {
                    endlineCount++; charCount += yyleng;
                    return yytext[0];
                }
{WHITESPACE}    {
                    whitespaceCount++; charCount++;
                }
{EOL}           { eolCount++; charCount++; }
"&&"            { return AND; }
"||"            { return OR; }
"=="            { return EQ; }
"!="            { return NEQ; }
">="            { return GEQ; }
"<="            { return LEQ; }
.               {
                    unknowncharCount++; charCount++;
                    return yytext[0];
                }

%%

/* Count how many endline characters are in the given string */
void count_eol(char *comment_string, size_t len)
{
    int i;
    char *p = comment_string;
   
    for (i = 0; p && i < len; p++, i++)
        if (*p == '\n')
            eolCount++;

    return;
}
