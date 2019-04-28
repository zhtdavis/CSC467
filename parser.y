%{
/***********************************************************************
 *   Interface to the parser module for CSC467 course project.
 * 
 *   Phase 2: Implement context free grammar for source language, and
 *            parse tracing functionality.
 *   Phase 3: Construct the AST for the source language program.
 ***********************************************************************/

/***********************************************************************
 *  C Definitions and external declarations for this module.
 *
 *  Phase 3: Include ast.h if needed, and declarations for other global or
 *           external vars, functions etc. as needed.
 ***********************************************************************/

#include <string.h>
#include "common.h"
#include "ast.h"
#include "symbol.h"
#include "semantic.h"
#define YYERROR_VERBOSE
#define yTRACE(x)    { if (traceParser) fprintf(traceFile, "%s\n", x); }

void yyerror(const char* s);    /* what to do in case of error            */
int yylex();              /* procedure for calling lexical analyzer */
extern int yyline;        /* variable holding current line number   */
extern symbol_table_entry *curr_table_entry;
extern node *ast;

int if_statement_line_num;

%}

/***********************************************************************
 *  Yacc/Bison declarations.
 *  Phase 2:
 *    1. Add precedence declarations for operators (after %start declaration)
 *    2. If necessary, add %type declarations for some nonterminals
 *  Phase 3:
 *    1. Add fields to the union below to facilitate the construction of the
 *       AST (the two existing fields allow the lexical analyzer to pass back
 *       semantic info, so they shouldn't be touched).
 *    2. Add <type> modifiers to appropriate %token declarations (using the
 *       fields of the union) so that semantic information can by passed back
 *       by the scanner.
 *    3. Make the %type declarations for the language non-terminals, utilizing
 *       the fields of the union as well.
 ***********************************************************************/

%{
#define YYDEBUG 1
%}


// TODO:Modify me to add more data types
// Can access me from flex useing yyval

%union {
  int as_int;
  char *as_id;
  float as_float;
  bool as_bool;
  int as_vec;
  struct node_ *as_ast;
}


// TODO:Replace myToken with your tokens, you can use these tokens in flex
%token           myToken1 myToken2 

// if/else
IF
ELSE

// {}/()/[]
LEFT_CBRACKET
RIGHT_CBRACKET
LEFT_BRACKET
RIGHT_BRACKET
LEFT_SBRACKET
RIGHT_SBRACKET

// ,
COMMA

// ;
SEMI_COLUMN

// true/false
BOOL_TRUE
BOOL_FALSE

// =
SINGLE_EQUAL

// bool, bvec2, bvec3, bvec4
BOOL
BVEC2
BVEC3
BVEC4

// int, ivec2, ivec3, ivec4
INT
IVEC2
IVEC3
IVEC4

// float, vec2, vec3, vec4
FLOAT
VEC2
VEC3
VEC4

// qualifier
CONST

// predefined functions
LIT 
DP3 
RSQ

// loops
WHILE

// void
VOID

// operators 
NOT
EXP
MULTI
DIVIDE
PLUS
MINUS
DOUBLE_EQUAL
NOT_EQUAL
LESS
LESS_EQUAL
GREATER
GREATER_EQUAL
LOGICAL_AND
LOGICAL_OR

// identifiers
%token <as_id> IDENTIFIER

// integer/float literal
%token <as_int> INTEGER_LITERAL
%token <as_float> FLOAT_LITERAL

// type declaration
%type <as_ast> scope 
%type <as_ast> declarations
%type <as_ast> statements
%type <as_ast> declaration
%type <as_ast> statement
%type <as_ast> type
%type <as_ast> expression
%type <as_ast> variable
%type <as_ast> arguments
%type <as_ast> arguments_opt



%nonassoc NO_ELSE
%nonassoc ELSE

%left LOGICAL_OR
%left LOGICAL_AND
%nonassoc DOUBLE_EQUAL NOT_EQUAL LESS LESS_EQUAL GREATER GREATER_EQUAL
%left PLUS MINUS
%left MULTI DIVIDE
%right EXP
%left NOT UNARY_MINUS
%left LEFT_BRACKET RIGHT_BRACKET LEFT_SBRACKET RIGHT_SBRACKET

%start    program
%%

/***********************************************************************
 *  Yacc/Bison rules
 *  Phase 2:
 *    1. Replace grammar found here with something reflecting the source
 *       language grammar
 *    2. Implement the trace parser option of the compiler
 *  Phase 3:
 *    1. Add code to rules for construction of AST.
 ***********************************************************************/
program
  :  scope	{ yTRACE("program -> scope") 
			  ast = $1; 
			  add_pre_defined_variable_entry();
  			  semantic_check(ast); }
  ;
scope 
  :  LEFT_CBRACKET declarations statements RIGHT_CBRACKET	{ yTRACE("scope -> { declarations statements }") 
															  $$ = ast_allocate(SCOPE_NODE, $2, $3); }
  ;
declarations
  :  declarations declaration	{ yTRACE("declarations -> declarations declaration") 
								  $$ = ast_allocate(DECLARATIONS_NODE, $1, $2); }
  |								{ yTRACE("declarations -> NULL") 
								  $$ = NULL; }
  ;
declaration
  :  type IDENTIFIER SEMI_COLUMN								{ yTRACE("declaration -> type IDENTIFIER ;") 
																  $$ = ast_allocate(DECLARATION_NODE, 0, $1, $2, NULL, yyline); }
  |  type IDENTIFIER SINGLE_EQUAL expression SEMI_COLUMN		{ yTRACE("declaration -> type IDENTIFIER = expression ;")
																  $$ = ast_allocate(DECLARATION_NODE, 0, $1, $2, $4, yyline); }
  |  CONST type IDENTIFIER SINGLE_EQUAL expression SEMI_COLUMN	{ yTRACE("declaration -> CONST type IDENTIFIER = expression ;") 
																  $$ = ast_allocate(DECLARATION_NODE, 1, $2, $3, $5, yyline); }
  ;
statements
  :  statements statement	{ yTRACE("statements -> statements statement") 
							  $$ = ast_allocate(STATEMENTS_NODE, $1, $2); }
  |							{ yTRACE("statements -> NULL") 
							  $$ = NULL; }
  ;
statement
  :  variable SINGLE_EQUAL expression SEMI_COLUMN						{ yTRACE("statement -> variable = expression ;") 
																		  $$ = ast_allocate(ASSIGNMENT_NODE, $1, $3, yyline); }
  |  IF LEFT_BRACKET expression RIGHT_BRACKET statement %prec NO_ELSE 	{ yTRACE("statement -> IF ( expression ) statement") 
																		  $$ = ast_allocate(IF_STATEMENT_NODE, $3, $5, NULL); }
  |  IF LEFT_BRACKET expression RIGHT_BRACKET statement	ELSE statement	{ yTRACE("statement -> IF ( expression ) statement ELSE statement") 
																		  $$ = ast_allocate(IF_STATEMENT_NODE, $3, $5, $7); }
  |  scope																{ yTRACE("statement -> scope") 
																		  $$ = ast_allocate(NESTED_SCOPE_NODE, $1); }	
  |  SEMI_COLUMN 														{ yTRACE("statement -> ;"); 
																		  $$ = NULL; }
  ;
arguments_opt
  :  arguments	{ yTRACE("arguments_opt -> arguments") 
				  $$ = ast_allocate(ARGUMENTS_NODE, $1, NULL); }
  |  			{ yTRACE("arguments_opt -> NULL") 
				  $$ = NULL; }
  ;
arguments
  :  arguments COMMA expression	{ yTRACE("arguments -> arguments , expression") 
								  $$ = ast_allocate(ARGUMENTS_NODE, $1, $3); }
  |  expression					{ yTRACE("arguments -> expression") 
								  $$ = ast_allocate(ARGUMENTS_NODE, NULL, $1); }
  ; 
expression
  :  type LEFT_BRACKET arguments RIGHT_BRACKET			{ yTRACE("expression -> type ( arguments )") 
												  	  	  $$ = ast_allocate(CONSTRUCTOR_NODE, $1, $3, yyline); }
  |  DP3 LEFT_BRACKET arguments_opt RIGHT_BRACKET		{ yTRACE("expression -> DP3 ( arguments_opt )") 
													  	  $$ = ast_allocate(FUNCTION_NODE, 0, $3, yyline); }
  |  LIT LEFT_BRACKET arguments_opt RIGHT_BRACKET		{ yTRACE("expression -> LIT ( arguments_opt )") 
													  	  $$ = ast_allocate(FUNCTION_NODE, 1, $3, yyline); }
  |  RSQ LEFT_BRACKET arguments_opt RIGHT_BRACKET		{ yTRACE("expression -> RSQ ( arguments_opt )") 
													  	  $$ = ast_allocate(FUNCTION_NODE, 2, $3, yyline); }
  |  INTEGER_LITERAL									{ yTRACE("expression -> INTEGER_LITERAL") 
													  	  $$ = ast_allocate(INT_NODE, $1, yyline); }
  |  FLOAT_LITERAL										{ yTRACE("expression -> FLOAT_LITERAL"); 
													  	  $$ = ast_allocate(FLOAT_NODE, $1, yyline); }
  |  BOOL_TRUE											{ yTRACE("expression -> BOOL_TRUE")
													  	  $$ = ast_allocate(BOOL_NODE, 1, yyline); }
  |  BOOL_FALSE											{ yTRACE("expression -> BOOL_FALSE")
													  	  $$ = ast_allocate(BOOL_NODE, 0, yyline); }
  |  variable 											{ yTRACE("expression -> variable")
														  $$ = ast_allocate(EXPR_VAR_NODE, $1, yyline); }
  |  NOT expression										{ yTRACE("expression -> ! expression")
														  $$ = ast_allocate(UNARY_EXPRESSION_NODE, '!', $2, yyline); }
  |  MINUS expression %prec UNARY_MINUS					{ yTRACE("expression -> unary - expresion")
														  $$ = ast_allocate(UNARY_EXPRESSION_NODE, '-', $2, yyline); }
  |  expression LOGICAL_AND	expression					{ yTRACE("expression -> expression && expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 0, $1, $3, yyline); }
  |  expression LOGICAL_OR expression					{ yTRACE("expression -> expression || expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 1, $1, $3, yyline); }
  |  expression DOUBLE_EQUAL expression					{ yTRACE("expression -> expression == expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 2, $1, $3, yyline); }
  |  expression NOT_EQUAL expression					{ yTRACE("expression -> expression != expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 3, $1, $3, yyline); }
  |  expression LESS expression							{ yTRACE("expression -> expression < expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 4, $1, $3, yyline); }
  |  expression LESS_EQUAL expression					{ yTRACE("expression -> expression <= expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 5, $1, $3, yyline); }
  |  expression GREATER expression						{ yTRACE("expression -> expression > expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 6, $1, $3, yyline); }
  |  expression GREATER_EQUAL expression				{ yTRACE("expression -> expression >= expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 7, $1, $3, yyline); }
  |  expression PLUS expression							{ yTRACE("expression -> expression + expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 8, $1, $3, yyline); }
  |  expression MINUS expression						{ yTRACE("expression -> expression - expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 9, $1, $3, yyline); }
  |  expression MULTI expression						{ yTRACE("expression -> expression * expression")
													  	  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 10, $1, $3, yyline); }
  |  expression DIVIDE expression						{ yTRACE("expression -> expression / expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 11, $1, $3, yyline); }
  |  expression EXP	expression							{ yTRACE("expression -> expression ^ expression")
														  $$ = ast_allocate(BINARY_EXPRESSION_NODE, 12, $1, $3, yyline); }
  |  LEFT_BRACKET expression RIGHT_BRACKET				{ yTRACE("expression -> ( expression )")
														  $$ = ast_allocate(NESTED_EXPRESSION_NODE, $2); }
  ;
variable
  :  IDENTIFIER												 { yTRACE("variable -> IDENTIFIER")
															   $$ = ast_allocate(VAR_NODE, $1, -1, yyline); }
  |  IDENTIFIER LEFT_SBRACKET INTEGER_LITERAL RIGHT_SBRACKET { yTRACE("variable -> IDENTIFIER [ INTEGER_LITERAL ]")
															   $$ = ast_allocate(VAR_NODE, $1, $3, yyline); }
  ;
type
  :  INT	{ yTRACE("type -> INT")
			  $$ = ast_allocate(TYPE_NODE, 0); }
  |  IVEC2	{ yTRACE("type -> IVEC2")
	          $$ = ast_allocate(TYPE_NODE, 1); }
  |  IVEC3	{ yTRACE("type -> IVEC3")
			  $$ = ast_allocate(TYPE_NODE, 2); }
  |  IVEC4	{ yTRACE("type -> IVEC4")
			  $$ = ast_allocate(TYPE_NODE, 3); }
  |  BOOL	{ yTRACE("type -> BOOL")
			  $$ = ast_allocate(TYPE_NODE, 4); }
  |  BVEC2	{ yTRACE("type -> BVEC2")
			  $$ = ast_allocate(TYPE_NODE, 5); }
  |  BVEC3	{ yTRACE("type -> BVEC3")
			  $$ = ast_allocate(TYPE_NODE, 6); }
  |  BVEC4	{ yTRACE("type -> BVEC4")
			  $$ = ast_allocate(TYPE_NODE, 7); }
  |  FLOAT	{ yTRACE("type -> FLOAT") 
			  $$ = ast_allocate(TYPE_NODE, 8); }
  |  VEC2	{ yTRACE("type -> VEC2")
			  $$ = ast_allocate(TYPE_NODE, 9); }
  |  VEC3	{ yTRACE("type -> VEC3")
			  $$ = ast_allocate(TYPE_NODE, 10); }
  |  VEC4	{ yTRACE("type -> VEC4")
			  $$ = ast_allocate(TYPE_NODE, 11); }
  ;
%%

/***********************************************************************ol
 * Extra C code.
 *
 * The given yyerror function should not be touched. You may add helper
 * functions as necessary in subsequent phases.
 ***********************************************************************/
void yyerror(const char* s) {
  if (errorOccurred)
    return;    /* Error has already been reported by scanner */
  else
    errorOccurred = 1;
        
  fprintf(errorFile, "\nPARSER ERROR, LINE %d",yyline);
  if (strcmp(s, "parse error")) {
    if (strncmp(s, "parse error, ", 13))
      fprintf(errorFile, ": %s\n", s);
    else
      fprintf(errorFile, ": %s\n", s+13);
  } else
    fprintf(errorFile, ": Reading token %s\n", yytname[YYTRANSLATE(yychar)]);
}

