/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CHARLIT = 258,
     NUMBER = 259,
     NAME = 260,
     TYPE = 261,
     FDECLARE = 262,
     DEFINE = 263,
     RETURN = 264,
     IF = 265,
     ELSE = 266,
     WHILE = 267,
     PRINT = 268,
     ARRAY = 269,
     STRLIT = 270,
     RANDOM = 271,
     TIME = 272,
     RESIZE = 273,
     SIZE = 274,
     ZEROS = 275,
     SET_ROTATE = 276,
     GET_ROTATE = 277,
     SET_MOVE = 278,
     GET_MOVE = 279,
     SET_SHIELDS = 280,
     GET_SHIELDS = 281,
     FIRE = 282,
     GET_ENERGY = 283,
     SCAN_DISTANCE = 284,
     SCAN_ANGLE = 285,
     SCAN_ID = 286,
     OR = 287,
     AND = 288,
     IFX = 289,
     LEQ = 290,
     GEQ = 291,
     NEQ = 292,
     EQ = 293,
     UMINUS = 294
   };
#endif
/* Tokens.  */
#define CHARLIT 258
#define NUMBER 259
#define NAME 260
#define TYPE 261
#define FDECLARE 262
#define DEFINE 263
#define RETURN 264
#define IF 265
#define ELSE 266
#define WHILE 267
#define PRINT 268
#define ARRAY 269
#define STRLIT 270
#define RANDOM 271
#define TIME 272
#define RESIZE 273
#define SIZE 274
#define ZEROS 275
#define SET_ROTATE 276
#define GET_ROTATE 277
#define SET_MOVE 278
#define GET_MOVE 279
#define SET_SHIELDS 280
#define GET_SHIELDS 281
#define FIRE 282
#define GET_ENERGY 283
#define SCAN_DISTANCE 284
#define SCAN_ANGLE 285
#define SCAN_ID 286
#define OR 287
#define AND 288
#define IFX 289
#define LEQ 290
#define GEQ 291
#define NEQ 292
#define EQ 293
#define UMINUS 294




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 119 "parser.y"
{
    char charval;
    int intval;
    char *strval;
    class ASTNode *node;
}
/* Line 1529 of yacc.c.  */
#line 134 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

