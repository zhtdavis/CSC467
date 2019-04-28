/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    myToken1 = 258,
    myToken2 = 259,
    IF = 260,
    ELSE = 261,
    LEFT_CBRACKET = 262,
    RIGHT_CBRACKET = 263,
    LEFT_BRACKET = 264,
    RIGHT_BRACKET = 265,
    LEFT_SBRACKET = 266,
    RIGHT_SBRACKET = 267,
    COMMA = 268,
    SEMI_COLUMN = 269,
    BOOL_TRUE = 270,
    BOOL_FALSE = 271,
    SINGLE_EQUAL = 272,
    BOOL = 273,
    BVEC2 = 274,
    BVEC3 = 275,
    BVEC4 = 276,
    INT = 277,
    IVEC2 = 278,
    IVEC3 = 279,
    IVEC4 = 280,
    FLOAT = 281,
    VEC2 = 282,
    VEC3 = 283,
    VEC4 = 284,
    CONST = 285,
    LIT = 286,
    DP3 = 287,
    RSQ = 288,
    WHILE = 289,
    VOID = 290,
    NOT = 291,
    EXP = 292,
    MULTI = 293,
    DIVIDE = 294,
    PLUS = 295,
    MINUS = 296,
    DOUBLE_EQUAL = 297,
    NOT_EQUAL = 298,
    LESS = 299,
    LESS_EQUAL = 300,
    GREATER = 301,
    GREATER_EQUAL = 302,
    LOGICAL_AND = 303,
    LOGICAL_OR = 304,
    IDENTIFIER = 305,
    INTEGER_LITERAL = 306,
    FLOAT_LITERAL = 307,
    NO_ELSE = 308,
    UNARY_MINUS = 309
  };
#endif
/* Tokens.  */
#define myToken1 258
#define myToken2 259
#define IF 260
#define ELSE 261
#define LEFT_CBRACKET 262
#define RIGHT_CBRACKET 263
#define LEFT_BRACKET 264
#define RIGHT_BRACKET 265
#define LEFT_SBRACKET 266
#define RIGHT_SBRACKET 267
#define COMMA 268
#define SEMI_COLUMN 269
#define BOOL_TRUE 270
#define BOOL_FALSE 271
#define SINGLE_EQUAL 272
#define BOOL 273
#define BVEC2 274
#define BVEC3 275
#define BVEC4 276
#define INT 277
#define IVEC2 278
#define IVEC3 279
#define IVEC4 280
#define FLOAT 281
#define VEC2 282
#define VEC3 283
#define VEC4 284
#define CONST 285
#define LIT 286
#define DP3 287
#define RSQ 288
#define WHILE 289
#define VOID 290
#define NOT 291
#define EXP 292
#define MULTI 293
#define DIVIDE 294
#define PLUS 295
#define MINUS 296
#define DOUBLE_EQUAL 297
#define NOT_EQUAL 298
#define LESS 299
#define LESS_EQUAL 300
#define GREATER 301
#define GREATER_EQUAL 302
#define LOGICAL_AND 303
#define LOGICAL_OR 304
#define IDENTIFIER 305
#define INTEGER_LITERAL 306
#define FLOAT_LITERAL 307
#define NO_ELSE 308
#define UNARY_MINUS 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 59 "parser.y" /* yacc.c:1909  */

  int as_int;
  char *as_id;
  float as_float;
  bool as_bool;
  int as_vec;
  struct node_ *as_ast;

#line 171 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
