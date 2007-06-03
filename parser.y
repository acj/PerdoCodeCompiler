/*
 *   CSE450 Project
 *   Adam Jensen (jensena8@cse.msu.edu)
 *   Ronald Nussbaum (nussbau3@cse.msu.edu)
 */

%{
    #include <fstream>
    #include <iostream>
    #include <map>
    #include <stack>
    #include <vector>
    #include "Assembler.h"
    #include "ASTAdd.h"
    #include "ASTAnd.h"
    #include "ASTArray.h"
    #include "ASTArrayIndex.h"
    #include "ASTAssignment.h"
    #include "ASTBlock.h"
    #include "ASTChar.h"
    #include "ASTCharVariable.h"
    #include "ASTDivide.h"
    #include "ASTEqual.h"
    #include "ASTExponent.h"
    #include "ASTFire.h"
    #include "ASTFunction.h"
    #include "ASTFunctionCall.h"
    #include "ASTGetEnergy.h"
    #include "ASTGetMove.h"
    #include "ASTGetRotate.h"
    #include "ASTGetShields.h"
    #include "ASTGreaterThan.h"
    #include "ASTGreaterThanEqual.h"
    #include "ASTIf.h"
    #include "ASTIfElse.h"
    #include "ASTLessThan.h"
    #include "ASTLessThanEqual.h"
    #include "ASTMod.h"
    #include "ASTMultiply.h"
    #include "ASTNode.h"
    #include "ASTNotEqual.h"
    #include "ASTOr.h"
    #include "ASTPrint.h"
    #include "ASTRandom.h"
    #include "ASTReturn.h"
    #include "ASTResize.h"
    #include "ASTScanAngle.h"
    #include "ASTScanDistance.h"
    #include "ASTScanId.h"
    #include "ASTSetMove.h"
    #include "ASTSetRotate.h"
    #include "ASTSetShields.h"
    #include "ASTSize.h"
    #include "ASTString.h"
    #include "ASTSubtract.h"
    #include "ASTTime.h"
    #include "ASTUnaryMinus.h"
    #include "ASTValue.h"
    #include "ASTVariable.h"
    #include "ASTWhile.h"
    #include "ASTZeros.h"
    #include "SymbolTable.h"
    using namespace std;

    // Imports from other modules
    extern int yylex();
    extern unsigned     eolCount;
    extern func_node    * func_add(char *, char *, char *);
    extern st_node      * sym_add(char *, char *);
    extern bool         func_exists(char *);
    extern bool         sym_exists(char *);
    extern bool         sym_init(char *, bool = false);

    static ASTBlock     *top_level;
    static ASTBlock     *top_level_func;
    static stack<ASTBlock *> blocks;
    static unsigned int return_label_count;
    static unsigned int type_check_index;
    unsigned int        var_count;
    unsigned int        label_count;
    unsigned int        current_scope;
    bool                function_context;
    vector<ASTReturn *> function_returns;

    void yyerror(char *error_string, char *detail="")
    {
        cout << "ERROR (line " << eolCount + 1 << "): " << error_string;
        if (strcmp(detail, ""))
            cout << ": " << detail << endl;
        else cout << endl;
        exit(1);
    }

    bool compare_block_types(ASTBlock *a, ASTBlock *b)
    {
        // Vacuous case
        if (a->getSize() != b->getSize())
            return false;

        int index;
        ASTNode *a_param, *b_param;
        for (index = 0; index < a->getSize(); index++)
        {
            a_param = a->getChild(index);
            b_param = b->getChild(index);

            if (a_param->getType() != b_param->getType()
                || a_param->getInternalType() != b_param->getInternalType())
            {
                return false;
            }
        }

        return true;
    }
%}

%union
{
    char charval;
    int intval;
    char *strval;
    class ASTNode *node;
};

%token <charval> CHARLIT
%token <intval> NUMBER
%token <strval> NAME TYPE FDECLARE DEFINE RETURN IF ELSE WHILE PRINT ARRAY 
            STRLIT RANDOM TIME RESIZE SIZE ZEROS SET_ROTATE GET_ROTATE 
            SET_MOVE GET_MOVE SET_SHIELDS GET_SHIELDS FIRE GET_ENERGY 
            SCAN_DISTANCE SCAN_ANGLE SCAN_ID
%left AND OR
%nonassoc IFX
%nonassoc ELSE
%nonassoc EQ NEQ '<' GEQ '>' LEQ
%left '+' '-'
%left '*' '/' '%'
%right '^'
%nonassoc UMINUS
%type <node> FUNCDECLARE FUNCDEF EXPR DECLARE STATEMENT STATEMENT_LIST ASSIGN 
            OPEN_BRACE PRINT_CMD P_CLOSE DEFPARAMLIST PARAMLIST DEFPARAM_CLOSE 
            PARAM_CLOSE
%type <strval> DECLARE_MULTIPLE NAME_DEFPARAM_OPEN

%%

STATEMENT_LIST:
    /* empty */ { }
    | STATEMENT_LIST STATEMENT
    {
        if ($2 != NULL)
            blocks.top()->addChild($2);
    }
    ;

STATEMENT:
    ';' { $$ = NULL; }
    | FUNCDECLARE
    {
        if ($1 != NULL)
            top_level_func->addChild($1);
        $$ = NULL;
    }
    | FUNCDEF
    {
        if ($1 != NULL)
            top_level_func->addChild($1);
        $$ = NULL;
    }
    | DECLARE ';' { $$ = $1 }
    | ASSIGN ';' { $$ = $1; }
    | EXPR ';' { $$ = $1; }
    | PRINT_CMD ';' { $$ = $1; }
    | RETURN EXPR ';'
    {
        if (!function_context)
        {
            yyerror("\"return\" used outside of function");
        }

        ASTReturn *ret = new ASTReturn($2);
        function_returns.push_back(ret);
        $$ = ret;
    }
    | OPEN_BRACE STATEMENT_LIST CLOSE_BRACE
    {
        $$ = $1;
    }
    | WHILE '(' EXPR ')' STATEMENT { $$ = new ASTWhile($3, $5); }
    | IF '(' EXPR ')' STATEMENT %prec IFX { $$ = new ASTIf($3, $5); }
    | IF '(' EXPR ')' STATEMENT ELSE STATEMENT
    {
        $$ = new ASTIfElse($3, $5, $7);
    }
    | RESIZE '(' NAME ',' EXPR ')' ';'
    {
	if (!sym_exists($3))
	    yyerror("Undeclared variable", $3);
	
	st_node *var_entry = sym_get($3);

	if (var_entry->type != "array")
	    yyerror("Invalid argument type");

	ASTArray *array = new ASTArray(string($3), var_entry);

	$$ = new ASTResize(array, $5);
    }
    | SET_ROTATE '(' EXPR ')' ';'
    {
        $$ = new ASTSetRotate($3);
    }
    | SET_MOVE '(' EXPR ')' ';'
    {
        $$ = new ASTSetMove($3);
    }
    | SET_SHIELDS '(' EXPR ')' ';'
    {
        $$ = new ASTSetShields($3);
    }
    | FIRE '(' EXPR ')' ';'
    {
        $$ = new ASTFire($3);
    }
    ;

OPEN_BRACE:
    '{' 
    { 
	ASTBlock *next_block = new ASTBlock();
	current_scope++; 
	blocks.push(next_block);
	$$ = next_block;
    }
    ;

CLOSE_BRACE:
    '}' 
    { 
	current_scope--; 
	sym_deactivate(); 
	blocks.pop();
    }
    ;

DECLARE:
    TYPE NAME
    {
        if (sym_exists($2))
            yyerror("Redeclaring variable", $2);
        else 
	{
	    if (!strcmp($1, "string"))
	    {
		st_node *var_entry = sym_add($2, "array");
		var_entry->var_num = var_count++;
		var_entry->internal_type = string("char");
	    }
	    else
	    {
		st_node *var_entry = sym_add($2, "scalar");
                var_entry->internal_type = $1;
		var_entry->var_num = var_count++;
	    }
	    $$ = NULL;
	}
    }
    | ARRAY '(' TYPE ')' NAME
    {
	if (sym_exists($5))
	    yyerror("Redeclaring variable", $5);
	else
	{
	    st_node *var_entry = sym_add($5, "array");
	    var_entry->var_num = var_count++;
	    var_entry->internal_type = string($3);
	}
	$$ = NULL;
    }
    | TYPE NAME '=' EXPR
    {
        if (sym_exists($2))
            yyerror("Redeclaring variable", $2);
        else
        {
            st_node *var_entry;
	    
	    if (!strcmp($1, "string"))
	    {
		var_entry = sym_add($2, "array");
		var_entry->internal_type = "char";
	    }
	    else
            {
		var_entry = sym_add($2, "scalar");
                var_entry->internal_type = $1;
            }

	    sym_init($2, true);
	    var_entry->var_num = var_count++;

	    if (var_entry->type == "array")
	    {
		ASTArray *array = new ASTArray(string($2), var_entry);
		$$ = new ASTAssignment(array, $4);
	    }
	    else if (var_entry->internal_type == "char")
	    {
		ASTCharVariable *var = new ASTCharVariable(string($2), 
						var_entry);
		$$ = new ASTAssignment(var, $4);
	    }
	    else
	    {
		ASTVariable *var = new ASTVariable(string($2), var_entry);
		$$ = new ASTAssignment(var, $4);
	    }
        }
    }
    | ARRAY '(' TYPE ')' NAME '=' EXPR
    {
	if (sym_exists($5))
	    yyerror("Redeclaring variable", $5);
	else
	{
	    st_node *var_entry = sym_add($5, "array");
	    sym_init($5, true);
	    var_entry->var_num = var_count++;
	    var_entry->internal_type = $3;

	    ASTArray *array = new ASTArray(string($5), var_entry);
	    array->setLvalue(true); // This array is an lvalue

	    $$ = new ASTAssignment(array, $7);
	}
    }
    | DECLARE_MULTIPLE NAME
    {
        if (sym_exists($2))
            yyerror("Redeclaring variable", $2);
        else
	{
	    if (!strcmp($1, "array_char"))
	    {
		st_node *var_entry = sym_add($2, "array");
		var_entry->internal_type = "char";
		var_entry->var_num = var_count++;
	    }
	    else if (!strcmp($1, "array_number"))
	    {
		st_node *var_entry = sym_add($2, "array");
		var_entry->internal_type = "number";
		var_entry->var_num = var_count++;
	    }
	    else
	    {
		st_node *var_entry = sym_add($2, $1);
		var_entry->var_num = var_count++;
	    }
	}

	$$ = NULL;
    }
    | DECLARE_MULTIPLE NAME '=' EXPR
    {
        if (sym_exists($2))
            yyerror("Redeclaring variable", $2);
        else
        {
	    if (!strcmp($1, "array_char"))
	    {
		st_node *var_entry = sym_add($2, "array");
		sym_init($2, true);
		var_entry->internal_type = "char";
		var_entry->var_num = var_count++;

		ASTArray *array = new ASTArray($2, var_entry);
		blocks.top()->addChild(new ASTAssignment(array, $4)); 
	    }
	    else if (!strcmp($1, "array_number"))
	    {
		st_node *var_entry = sym_add($2, "array");
		sym_init($2, true);
		var_entry->internal_type = "number";
		var_entry->var_num = var_count++;

		ASTArray *array = new ASTArray($2, var_entry);
		blocks.top()->addChild(new ASTAssignment(array, $4));
	    }
	    else
	    {
		st_node *var_entry = sym_add($2, $1);
		sym_init($2, true);
		var_entry->var_num = var_count++;

		if (var_entry->type == "char")
		{
		    ASTCharVariable *var = new ASTCharVariable(string($2), 
						    var_entry);
		    blocks.top()->addChild(new ASTAssignment(var, $4));
		}
		else
		{
		    ASTVariable *var = new ASTVariable(string($2), var_entry);
		    blocks.top()->addChild(new ASTAssignment(var, $4));
		}
	    }
        }
	
	$$ = NULL;
    }
    ;

DECLARE_MULTIPLE:
    TYPE NAME ','
    {
        if (sym_exists($2))
            yyerror("Redeclaring variable", $2);
        else
	{
	    st_node *var_entry;
	    
	    if (!strcmp($1, "string"))
	    {
		var_entry = sym_add($2, "array");
		var_entry->internal_type = "string";

		$$ = "array_char";
	    }
	    else
	    {
                var_entry = sym_add($2, "scalar");
		var_entry->var_num = var_count++;
                var_entry->internal_type = $1;
		$$ = $1; // Pass up the type of variable
	    }
	}
    }
    | ARRAY '(' TYPE ')' NAME ','
    {
	if (sym_exists($5))
	    yyerror("Redeclaring variable", $3);
	else
	{
	    st_node *var_entry = sym_add($5, "array");
	    var_entry->var_num = var_count++;
	    var_entry->internal_type = $3;
	    string array_type = string("array_") + string($3);

	    // FIXME: Ugly and lame
	    char *return_type = strdup(array_type.c_str());
	    $$ = return_type;
	}
    }
    | TYPE NAME '=' EXPR ','
    {
        if (sym_exists($2))
            yyerror("Redeclaring variable", $2);
        else if (!strcmp($1, "string"))
	{
            st_node *var_entry = sym_add($2, "array");
	    var_entry->internal_type = "char";

	    ASTArray *array = new ASTArray($2, var_entry);
	    blocks.top()->addChild(new ASTAssignment(array, $4));

	    $$ = "array_char";
	}
	else
        {
	    st_node *var_entry = sym_add($2, $1);
	    sym_init($2, true);
	    var_entry->var_num = var_count++;

	    if (var_entry->type == "char")
	    {
		ASTCharVariable *var = new ASTCharVariable(string($2),
                                                var_entry);
		blocks.top()->addChild(new ASTAssignment(var, $4));
	    }
	    else
	    {
		ASTVariable *var = new ASTVariable(string($2), var_entry);
		blocks.top()->addChild(new ASTAssignment(var, $4));
	    }
	    $$ = $1; 
        }
    }
    | ARRAY '(' TYPE ')' NAME '=' EXPR ','
    {
	if (sym_exists($5))
	    yyerror("Redeclaring variable", $5);
	else
	{
	    st_node *var_entry = sym_add($5, "array");
	    sym_init($5, true);
	    var_entry->var_num = var_count++;
	    var_entry->internal_type = $3;

	    ASTArray *array = new ASTArray(string($5), var_entry);
	    array->setLvalue(true); // This array is an lvalue

	    blocks.top()->addChild(new ASTAssignment(array, $7));

	    string array_type = string("array_") + string($3);

	    $$ = strdup(array_type.c_str());
	}
    }
    | DECLARE_MULTIPLE NAME ','
    {
        if (sym_exists($2))
            yyerror("Redeclaring variable", $2);
        else
	{
	    if (!strcmp($1, "array_char"))
	    {
		st_node *var_entry = sym_add($2, "array");
		var_entry->internal_type = "char";
		var_entry->var_num = var_count++;
	    }
	    else if (!strcmp($1, "array_number"))
	    {
		st_node *var_entry = sym_add($2, "array");
		var_entry->internal_type = "number";
		var_entry->var_num = var_count++;
	    }
	    else
	    {
		st_node *var_entry = sym_add($2, $1);
		var_entry->var_num = var_count++;
	    }
	}
    }
    | DECLARE_MULTIPLE NAME '=' EXPR ','
    {
        if (sym_exists($2))
            yyerror("Redeclaring variable", $2);
        else
        {
            st_node *var_entry = sym_add($2, $1);
	    sym_init($2, true);
	    var_entry->var_num = var_count++;

	    if (var_entry->type == "char")
	    {
		ASTCharVariable *var = new ASTCharVariable(string($2),
					    var_entry);
		blocks.top()->addChild(new ASTAssignment(var, $4));
	    }
	    else
	    {
		ASTVariable *var = new ASTVariable(string($2), var_entry);
		blocks.top()->addChild(new ASTAssignment(var, $4));
	    }
        }
    }
    ;

ASSIGN:
    NAME '=' EXPR
    {
        if (sym_exists($1))
	{
	    sym_init($1, true);
	    st_node *var_entry = sym_get($1);

	    if (var_entry->type == "array")
	    {
		ASTArray *array = new ASTArray(string($1), var_entry);
		$$ = new ASTAssignment(array, $3);
	    }
	    else
	    {
		if (var_entry->internal_type == "char")
		{
		    ASTCharVariable *var = new ASTCharVariable(string($1),
		                                                var_entry);
		    $$ = new ASTAssignment(var, $3);
		}
		else
		{
		    ASTVariable *var = new ASTVariable(string($1), var_entry);
		    $$ = new ASTAssignment(var, $3);
		}
	    }
	}
        else yyerror("Unknown variable", $1);
    }
    | NAME '[' EXPR ']' '=' EXPR
    {
	if ($3->getType() != "scalar" || $3->getInternalType() != "number") 
	    yyerror("Invalid array index type", strdup($3->getType().c_str()));

	if (sym_exists($1))
	{
	    st_node *sym = sym_get($1);

	    if (sym->type != "array")
	    {
		yyerror("Attempt to index non-array type", strdup($1));
	    }

	    string array_int_type = sym->internal_type;

            if (array_int_type != $6->getInternalType())
		yyerror("Type mismatch in array assignment");
            else
	    {
		sym_init($1, true);
		st_node *var_entry = sym_get($1);

		ASTArrayIndex *var 
                    = new ASTArrayIndex(string($1), $3, true, var_entry);

		$$ = new ASTAssignment(var, $3, $6);
	    }
        }
	else yyerror("Unknown variable", $1);
    }
    ;

EXPR:
    NUMBER { $$ = new ASTValue($1); }
    | CHARLIT { $$ = new ASTChar($1); }
    | STRLIT 
    { 
        // Use the literal string as its symbol name
        char encoded_lit[SYMSIZE];
        sprintf(encoded_lit, "\"%s\"", $1);
        st_node *sym = sym_add(encoded_lit, "array");
        sym->internal_type = "char";

        $$ = new ASTString(string($1, 1, strlen($1) - 2), sym); 
    }
    | SIZE '(' EXPR ')'
    {
	$$ = new ASTSize($3);
    }
    | RANDOM '(' EXPR ')'
    {
	$$ = new ASTRandom($3);
    }
    | TIME '(' ')'
    {
        $$ = new ASTTime();
    }
    | ZEROS '(' EXPR ')'
    {
	$$ = new ASTZeros($3);

        // Use an encoded name as the symbol name
        char encoded[SYMSIZE];
        sprintf(encoded, "zeros\\%d", $$->getVarNum());
        st_node *sym = sym_add(encoded, "array");
        sym->internal_type = "number";
        sym->var_num = $$->getVarNum();
    }
    | NAME
    {
        if (!sym_exists($1))
            yyerror("Unknown variable", $1);
        else if (!sym_init($1))
            yyerror("Uninitialized variable", $1);
        else
	{
	    st_node *sym = sym_get($1);

	    // Is this an array?
	    if (sym->type == "array")
		$$ = new ASTArray(string($1), sym);
	    else if (sym->internal_type == "char")
		$$ = new ASTCharVariable(string($1), sym);
	    else
		$$ = new ASTVariable(string($1), sym); 
	}
    }
    | NAME PARAM_OPEN PARAMLIST PARAM_CLOSE
    {
	if (!func_exists($1))
	    yyerror("Undeclared function", $1);
        else
        {
            func_node *func = func_get($1);

            ASTFunction *fptr = (ASTFunction *)func->func;
	    $$ = new ASTFunctionCall($1, (ASTBlock *)$4, fptr);
        }
    }
    | NAME PARAM_OPEN PARAM_CLOSE
    {
        if (!func_exists($1))
            yyerror("Undeclared function", $1);
        else
        {
            func_node *func = func_get($1);

            ASTFunction *fptr = (ASTFunction *)func->func;
            $$ = new ASTFunctionCall($1, NULL, fptr);
        }
    }
    | NAME '[' EXPR ']'
    {
	if (!sym_exists($1))
	    yyerror("Unknown variable", $1);
	else if (!sym_init($1))
	    yyerror("Uninitialized variable", $1);
	else if ($3->getType() != "scalar" || $3->getInternalType() != "number")
	    yyerror("Invalid array index type", strdup($3->getType().c_str()));

	st_node *sym = sym_get($1);

	if (sym->type != "array")
	    yyerror("Attempt to index non-array", $1);

	$$ = new ASTArrayIndex($1, $3, false, sym);	
    }
    | EXPR AND EXPR %prec AND { $$ = new ASTAnd($1, $3); }
    | EXPR OR EXPR %prec OR { $$ = new ASTOr($1, $3); }
    | EXPR EQ EXPR %prec EQ { $$ = new ASTEqual($1, $3); }
    | EXPR NEQ EXPR %prec NEQ { $$ = new ASTNotEqual($1, $3); }
    | EXPR '>' EXPR { $$ = new ASTGreaterThan($1, $3); }
    | EXPR GEQ EXPR %prec GEQ { $$ = new ASTGreaterThanEqual($1, $3); }
    | EXPR '<' EXPR { $$ = new ASTLessThan($1, $3); }
    | EXPR LEQ EXPR %prec LEQ { $$ = new ASTLessThanEqual($1, $3); }
    | EXPR '+' EXPR 
    { 
        if ($1->getClass() == "ASTValue" && $3->getClass() == "ASTValue")
            $$ = new ASTValue($1->getValue() + $3->getValue()); 
        else if ($1->getClass() == "ASTValue" && $1->getValue() == 0)
            $$ = $3;
        else if ($3->getClass() == "ASTValue" && $3->getValue() == 0)
            $$ = $1;
        else
            $$ = new ASTAdd($1, $3);
    }
    | EXPR '-' EXPR 
    {
        if ($1->getClass() == "ASTValue" && $3->getClass() == "ASTValue")
            $$ = new ASTValue($1->getValue() - $3->getValue()); 
        else if ($1->getClass() == "ASTValue" && $1->getValue() == 0)
            $$ = $3;
        else if ($3->getClass() == "ASTValue" && $3->getValue() == 0)
            $$ = $1;
        else
            $$ = new ASTSubtract($1, $3); 
    }
    | EXPR '*' EXPR
    {
        if ($1->getClass() == "ASTValue" && $3->getClass() == "ASTValue")
            $$ = new ASTValue($1->getValue() * $3->getValue()); 
        else if ($1->getClass() == "ASTValue" && $1->getValue() == 1)
            $$ = $3;
        else if ($3->getClass() == "ASTValue" && $3->getValue() == 1)
            $$ = $1;
        else
            $$ = new ASTMultiply($1, $3);
    }
    | EXPR '/' EXPR
    {
        if ($3 == 0)
            yyerror("Division by 0");
        else 
        {
            if ($1->getClass() == "ASTValue" && $3->getClass() == "ASTValue")
                $$ = new ASTValue($1->getValue() / $3->getValue()); 
            else if ($3->getClass() == "ASTValue" && $3->getValue() == 1)
                $$ = $1;
            else
                $$ = new ASTDivide($1, $3);
        }
    }
    | EXPR '%' EXPR
    {
        if ($3 == 0)
            yyerror("Division by 0");
        else 
            $$ = new ASTMod($1, $3);
    }
    | EXPR '^' EXPR { $$ = new ASTExponent($1, $3); }
    | '-' EXPR %prec UMINUS { $$ = new ASTUnaryMinus($2); } 
    | '(' EXPR ')' { $$ = $2; }
    | GET_ROTATE '(' ')'
    {
        $$ = new ASTGetRotate();
    }
    | GET_MOVE '(' ')'
    {
        $$ = new ASTGetMove();
    }
    | GET_SHIELDS '(' ')'
    {
        $$ = new ASTGetShields();
    }
    | GET_ENERGY '(' ')'
    {
        $$ = new ASTGetEnergy();
    }
    | SCAN_DISTANCE '(' ')'
    {
        $$ = new ASTScanDistance();
    }
    | SCAN_ANGLE '(' ')'
    {
        $$ = new ASTScanAngle();
    }
    | SCAN_ID '(' ')'
    {
        $$ = new ASTScanId();
    }
    ;

FUNCDECLARE:
    FDECLARE TYPE NAME_DEFPARAM_OPEN DEFPARAM_CLOSE
    {
        func_node *node; 

        // Check for redeclaration
        if (func_exists($3))
        {
            node = func_get($3);

            // If this function has already been defined, give an error 
            if (node->declared)
                yyerror("Function redeclared", $3);
        }

        // Handle the string type properly (it's an array)
        if (!strcmp($2, "string"))
            node = func_add($3, "array", "char");
        else node = func_add($3, "scalar", $2);

        node->defined = false;

        // Set up a skeleton function object (no function body yet)
        ASTFunction *fptr = new ASTFunction($3, $4, NULL, node);
        node->func = fptr;
        $$ = fptr;

        current_scope--;
        function_context = false;
        sym_set_current_function("main");
    }
    | FDECLARE TYPE NAME_DEFPARAM_OPEN DEFPARAMLIST DEFPARAM_CLOSE
    {
        func_node *node; 

        // Check for redeclaration
        if (func_exists($3))
        {
            node = func_get($3);

            // If this function has already been defined, give an error 
            if (node->declared)
                yyerror("Function redeclared", $3);
        }

        // Handle the string type properly (it's an array)
        if (!strcmp($2, "string"))
            node = func_add($3, "array", "char");
        else node = func_add($3, "scalar", $2);

        node->defined = false;

        // Set up a skeleton function object (no function body yet)
        ASTFunction *fptr = new ASTFunction($3, $5, NULL, node);
        node->func = fptr;
        $$ = fptr;

        current_scope--;
        function_context = false;
        sym_set_current_function("main");
    }

FUNCDEF:
    DEFINE TYPE NAME_DEFPARAM_OPEN DEFPARAMLIST DEFPARAM_CLOSE STATEMENT 
    {
        func_node *node;
        ASTFunction *fptr;

        // Check for prior declaration or redefinition
        if (func_exists($3))
        {
            node = func_get($3);

            if (node->declared)
            {
                fptr = (ASTFunction *)node->func;

                // Verify return type before attaching the body
                if (fptr->getType() != string("scalar")
                    || fptr->getInternalType() != string($2))
                {
                    yyerror("Return type does not match declaration", $3);
                }

                fptr->setFunctionBody((ASTBlock *)$6);

                node->defined = true;
            }
            else if (node->defined)
                yyerror("Function redefinition", $3);
            else
                yyerror("Function neither declared nor defined", $3);
        }
        else
        {
            // Handle the string type properly (it's an array)
            if (!strcmp($2, "string"))
                node = func_add($3, "array", "char");
            else node = func_add($3, "scalar", $2);

            node->defined = true;

            fptr = new ASTFunction($3, $5, (ASTBlock *)$6, node);
            node->func = fptr;

            current_scope--;
            function_context = false;
            sym_set_current_function("main"); 
        }
            
        // Process any returns
        if (function_returns.size() > 0)
        {
            vector<ASTReturn *>::const_iterator return_iter;

            for (return_iter = function_returns.begin();
                return_iter != function_returns.end();
                return_iter++)
            {
                (*return_iter)->setSymTblEntry(node);

                if ((*return_iter)->getType() != node->type
                    || (*return_iter)->getInternalType() != node->internal_type)
                {
                    yyerror("Return type does not match return value");
                }
            }

            function_returns.clear();
        }
        
        $$ = fptr; 
    }
    | DEFINE ARRAY '(' TYPE ')' NAME_DEFPARAM_OPEN DEFPARAMLIST DEFPARAM_CLOSE 
        STATEMENT
    {
        func_node *node;
        ASTFunction *fptr;

        // Check for prior declaration or redefinition
        if (func_exists($6))
        {
            node = func_get($6);

            if (node->declared)
            {
                // Verify number of parameters
                ASTBlock *param_block = (ASTBlock *)node->func->leftChild();
                ASTBlock *def_block = (ASTBlock *)$8;

                // Verify the number and type of parameters
                if (!compare_block_types(param_block, def_block))
                    yyerror("Type mismatch in function parameters", $6);

                // All clear -- set up the function body.
                fptr = (ASTFunction *)node->func;
                
                // Verify return type before attaching the body
                if (fptr->getType() != string("array")
                    || fptr->getInternalType() != string($4))
                {
                    yyerror("Return type does not match declaration", $6);
                }
                fptr->setFunctionBody((ASTBlock *)$9);

                node->defined = true;
            }
            else if (node->defined)
                yyerror("Function redefinition", $6);
        }
        else
        {
            node = func_add($6, "array", $4);
            fptr = new ASTFunction($6, $8, (ASTBlock *)$9, node);
            node->func = fptr;

            node->defined = true;

            current_scope--;
            function_context = false;
            sym_set_current_function("main");
        }
        
        // Process any returns
        if (function_returns.size() > 0)
        {
            vector<ASTReturn *>::const_iterator return_iter;

            for (return_iter = function_returns.begin();
                return_iter != function_returns.end();
                return_iter++)
            {
                (*return_iter)->setSymTblEntry(node);

                if ((*return_iter)->getType() != node->type
                    || (*return_iter)->getInternalType() != node->internal_type)
                {
                    yyerror("Return type does not match return value");
                }
            }

            function_returns.clear();
        }
        
        $$ = fptr; 
    }
    | DEFINE TYPE NAME_DEFPARAM_OPEN DEFPARAM_CLOSE STATEMENT
    {
        func_node *node;
        ASTFunction *fptr;

        // Check for prior declaration or redefinition
        if (func_exists($3))
        {
            node = func_get($3);

            if (node->declared)
            {
                // All clear -- set up the function body.
                fptr = (ASTFunction *)node->func;
                
                // Verify return type before attaching the body
                if (fptr->getType() != string("scalar")
                    || fptr->getInternalType() != string($2))
                {
                    yyerror("Return type does not match declaration", $3);
                }
                fptr->setFunctionBody((ASTBlock *)$5);
                
                node->defined = true;
            }
            else if (node->defined)
                yyerror("Function redefinition", $3);
        }
        else
        {
            // Handle the string type properly (it's an array)
            if (!strcmp($2, "string"))
                node = func_add($3, "array", "char");
            else node = func_add($3, "scalar", $2);

            node->defined = true;

            fptr = new ASTFunction($3, $4, (ASTBlock *)$5, node);
            node->func = fptr;

            current_scope--;
            function_context = false;
            sym_set_current_function("main");
        }
        
        // Process any returns
        if (function_returns.size() > 0)
        {
            vector<ASTReturn *>::const_iterator return_iter;

            for (return_iter = function_returns.begin();
                return_iter != function_returns.end();
                return_iter++)
            {
                (*return_iter)->setSymTblEntry(node);

                if ((*return_iter)->getType() != node->type
                    || (*return_iter)->getInternalType() != node->internal_type)
                {
                    yyerror("Return type does not match return value");
                }
            }

            function_returns.clear();
        }
        
        $$ = fptr; 
    }
    | DEFINE ARRAY '(' TYPE ')' NAME_DEFPARAM_OPEN DEFPARAM_CLOSE STATEMENT
    {
        func_node *node;
        ASTFunction *fptr;

        // Check for prior declaration or redefinition
        if (func_exists($6))
        {
            node = func_get($6);

            if (node->declared)
            {
                // All clear -- set up the function body.
                fptr = (ASTFunction *)node->func;
                
                // Verify return type before attaching the body
                if (fptr->getType() != string("array")
                    || fptr->getInternalType() != string($4))
                {
                    yyerror("Return type does not match declaration", $6);
                }
                fptr->setFunctionBody((ASTBlock *)$8);

                node->defined = true;
            }
            else if (node->defined)
                yyerror("Function redefinition", $6);
        }
        else
        {
            node = func_add($6, "array", $4);
            fptr = new ASTFunction($6, $7, (ASTBlock *)$8, node);
            node->func = fptr;

            node->defined = true;

            current_scope--;
            function_context = false;
            sym_set_current_function("main");
        }
        
        // Process any returns
        if (function_returns.size() > 0)
        {
            vector<ASTReturn *>::const_iterator return_iter;

            for (return_iter = function_returns.begin();
                return_iter != function_returns.end();
                return_iter++)
            {
                (*return_iter)->setSymTblEntry(node);

                if ((*return_iter)->getType() != node->type
                    || (*return_iter)->getInternalType() != node->internal_type)
                {
                    yyerror("Return type does not match return value");
                }
            }

            function_returns.clear();
        }
        
        $$ = fptr; 
    }
    ;

PARAM_OPEN:
    '('
    { 
        blocks.push(new ASTBlock());
        current_scope++;
    }
    ;

PARAM_CLOSE:
    ')'
    { 
        $$ = blocks.top(); 
        blocks.pop();
        current_scope--;
    }
    ;

NAME_DEFPARAM_OPEN:
    NAME '('
    { 
        type_check_index = 0;
        sym_set_current_function($1);
        blocks.push(new ASTBlock());
        function_context = true;
        current_scope++;
        $$ = $1;
    }
    ;

DEFPARAM_CLOSE:
    ')'
    {
        if (func_exists(sym_get_current_function()))
        {
            func_node *node = func_get(sym_get_current_function());
            ASTFunction *func = (ASTFunction *)node->func;
            ASTBlock *params = (ASTBlock *)func->leftChild();

            if (params->getSize() != type_check_index)
            {
                yyerror("Incorrect number of arguments in function definition", 
                    sym_get_current_function());
            }
        }

        $$ = blocks.top(); 
        blocks.pop();
    }
    ;

DEFPARAMLIST:
    DEFPARAMLIST ',' TYPE NAME 
    {
        // If the function already exists, use the symbols from the
        // function declaration.
        if (func_exists(sym_get_current_function()))
        {
            // Check the type
            func_node *node = func_get(sym_get_current_function());
            ASTFunction *func = (ASTFunction *)node->func;
            ASTBlock *params = (ASTBlock *)func->leftChild();
            ASTNode *child = params->getChild(type_check_index);

            if (child == NULL)
            {
                // Non-existent child (probably a parameter count mismatch)
                yyerror("Function definition does not match declaration", $4);
            }
            else if (child->getType() != "scalar" 
                || child->getInternalType() != string($3))
            {
                yyerror("Function definition does not match declaration", $4);
            }

            type_check_index++;
        }
        else
        {
            if (!strcmp($3, "string"))
            {
                st_node *sym = sym_add($4, "array");
                sym->var_num = var_count++;
                sym->internal_type = "char";
                sym->init = true;

                blocks.top()->addChild(new ASTArray($4, sym));
            }
            else
            {
                st_node *sym = sym_add($4, "scalar");
                sym->var_num = var_count++;
                sym->internal_type = string($3);
                sym->init = true;

                if (sym->internal_type == "number")
                    blocks.top()->addChild(new ASTVariable($4, sym));
                else
                    blocks.top()->addChild(new ASTCharVariable($4, sym));
            }
        }
    }
    | DEFPARAMLIST ',' ARRAY '(' TYPE ')' NAME
    {
        // If the function already exists, use the symbols from the
        // function declaration.
        if (func_exists(sym_get_current_function()))
        {
            // Check the type
            func_node *node = func_get(sym_get_current_function());

            ASTFunction *func = (ASTFunction *)node->func;
            ASTBlock *params = (ASTBlock *)func->leftChild();
            ASTNode *child = params->getChild(type_check_index);

            if (child == NULL)
            {
                // Non-existent child (probably a parameter count mismatch)
                yyerror("Function definition does not match declaration", $7);
            }
            else if (child->getType() != "array" 
                || child->getInternalType() != string($5))
            {
                yyerror("Function definition does not match declaration", $7);
            }

            type_check_index++;
        }
        else
        {
            st_node *sym = sym_add($7, "array");
            sym->var_num = var_count++;
            sym->internal_type = $5;
            sym->init = true;

            blocks.top()->addChild(new ASTArray($7, sym)); 
        }
    }
    | TYPE NAME
    {
        // If the function already exists, use the symbols from the
        // function declaration.
        if (func_exists(sym_get_current_function()))
        {
            // Check the type
            func_node *node = func_get(sym_get_current_function());
            ASTFunction *func = (ASTFunction *)node->func;
            ASTBlock *params = (ASTBlock *)func->leftChild();
            ASTNode *child = params->getChild(type_check_index);

            if (child == NULL)
            {
                // Non-existent child (probably a parameter count mismatch)
                yyerror("Function definition does not match declaration", $2);
            }
            else if (!strcmp($1, "string"))
            {
                if (child->getType() != "array" 
                    || child->getInternalType() != "char")
                {
                    yyerror("Function definition does not match declaration", 
                            $2);
                }
            }
            else
            {
                if ((child->getType() != "scalar"
                    && child->getInternalType() != string($1)))
                {
                    yyerror("Function definition does not match declaration", 
                            $2);
                }
            }

            type_check_index++;
        }
        else
        {
            if (!strcmp($1, "string"))
            {
                st_node *sym = sym_add($2, "array");
                sym->var_num = var_count++;
                sym->internal_type = "char";
                sym->init = true;

                blocks.top()->addChild(new ASTArray($2, sym));
            }
            else
            {
                st_node *sym = sym_add($2, "scalar");
                sym->var_num = var_count++;
                sym->internal_type = string($1);
                sym->init = true;

                if (sym->internal_type == "number")
                    blocks.top()->addChild(new ASTVariable($2, sym));
                else
                    blocks.top()->addChild(new ASTCharVariable($2, sym));
            }
        }
    }
    | ARRAY '(' TYPE ')' NAME
    {
        // If the function already exists, use the symbols from the
        // function declaration.
        if (func_exists(sym_get_current_function()))
        {

            // Check the type
            func_node *node = func_get(sym_get_current_function());
            ASTFunction *func = (ASTFunction *)node->func;
            ASTBlock *params = (ASTBlock *)func->leftChild();
            ASTNode *child = params->getChild(type_check_index);

            if (child == NULL)
            {
                // Non-existent child (probably a parameter count mismatch)
                yyerror("Function definition does not match declaration", $5);
            }
            else if (child->getType() != "array" 
                || child->getInternalType() != string($3))
            {
                yyerror("Function definition does not match declaration", $5);
            }

            type_check_index++;
        }
        else
        {
            st_node *sym = sym_add($5, "array");
            sym->var_num = var_count++;
            sym->internal_type = string($3);
            sym->init = true;

            blocks.top()->addChild(new ASTArray($5, sym)); 
        }
    }
    ;

PARAMLIST:
    PARAMLIST ',' EXPR
    {
	blocks.top()->addChild($3);
    }
    | EXPR
    {
	blocks.top()->addChild($1);
    }
    ;

PRINT_CMD:
    PRINT P_OPEN MULTI_PRINT P_CLOSE { $$ = $4; }
    ;

P_OPEN:
    '(' { blocks.push(new ASTBlock()); }
    ;

P_CLOSE:
    ')' 
    { 
        if (blocks.top()->getLastChild() != 0)
        {
            ASTPrint *node = (ASTPrint *)blocks.top()->getLastChild();
            node->setNewline(true);
        }

        $$ = blocks.top();
        blocks.pop(); 
    }
    ;

MULTI_PRINT:
    MULTI_PRINT ',' EXPR { blocks.top()->addChild(new ASTPrint($3)); }
    | EXPR { blocks.top()->addChild(new ASTPrint($1)); }
    ;

%%

extern FILE *yyin;
static Assembler *assembler;

// Add an intermediate code command
void add_int_command(string command)
{
    assembler->add_int_code(command);
}

int main(int argc, char **argv)
{
    string out_file = "";
    bool intermediate_out = false;

    if (argc == 3)
    {
        if  (!(yyin = fopen(argv[1], "r")))
        {
            cerr << "Error opening " << argv[1] << endl;
            exit(1);
        }

	out_file = argv[2];
    }
    else if (argc == 4 && !strcmp(argv[1], "-i"))
    {
	// The "-i" flag has been passed, so we want to output
	// perdo intermediate code.

	if (!(yyin = fopen(argv[2], "r")))
	{
	    cerr << "Error opening " << argv[2] << endl;
	    exit(1);
	}

	out_file = argv[3];
	intermediate_out = true;
    }
    else
    {
        cout << "Usage is " << argv[0] << " FILE.perdo FILE.pci" << endl;
        exit(1);
    }

    var_count = 2;
    label_count = 0;
    current_scope = 0;
    function_context = false; // Begin in normal (global) context
    return_label_count = 0;
    type_check_index = 0;

    assembler = new Assembler(out_file);

    // The top-most block (scope) is the top-level
    top_level = new ASTBlock();
    blocks.push(top_level);
    top_level_func = new ASTBlock();

    yyparse();
    cout << "Parse successful!\n";

    // Traverse our top-level statements
    add_int_command("jump _main");
    top_level_func->genIntCode();
    add_int_command("_main:");
    top_level->genIntCode();

    // Produce our intermediate or assembly code
    if (intermediate_out)
    {
	assembler->output_intermediate();
    }
    else
    {
	assembler->translate();
    }

    return EXIT_SUCCESS;
}
