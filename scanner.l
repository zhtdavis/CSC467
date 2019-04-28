%{
/**********************************************************************
 *  Interface to the scanner module for CSC467 course project
 **********************************************************************/


#include "common.h"
#include "parser.tab.h"
#include "string.h"
#include <stdlib.h>
#include <math.h>


#define YY_USER_INIT { yyin = inputFile; }
#define	yyinput      input
#define yTRACE(x)    { if (traceScanner) fprintf(traceFile, "TOKEN %3d : %s\n", x, yytext); }
#define yERROR(x)    { fprintf(errorFile, "\nLEXICAL ERROR, LINE %d: %s\n", yyline, x); errorOccurred = TRUE; yyterminate(); }

int CheckInt(void);
int yyline = 1;

%}
%option noyywrap

WS        [ \t]
LOOKAHEAD [ \t\n\;\,\{\}\(\)\[\]\+\-\*\/\>\<\=\!\&\|\^]
INT_LIT   ([1-9][0-9]*)|0
FLT_LIT	  (\.[0-9]+)|([1-9][0-9]*\.[0-9]*)|(0\.[0-9]*)

%%

if/{LOOKAHEAD}		{ yTRACE(IF); return IF; }
else/{LOOKAHEAD}	{ yTRACE(ELSE); return ELSE; }

true/{LOOKAHEAD}	{ yylval.as_bool = true; yTRACE(BOOL_TRUE); return BOOL_TRUE; }
false/{LOOKAHEAD} 	{ yylval.as_bool = false; yTRACE(BOOL_FALSE); return BOOL_FALSE; }

bool/{LOOKAHEAD}	{ yTRACE(BOOL); return BOOL; }
bvec2/{LOOKAHEAD}	{ yTRACE(BVEC2); return BVEC2; }
bvec3/{LOOKAHEAD}	{ yTRACE(BVEC3); return BVEC3; }
bvec4/{LOOKAHEAD}	{ yTRACE(BVEC4); return BVEC4; }

int/{LOOKAHEAD}		{ yTRACE(INT); return INT; }
ivec2/{LOOKAHEAD}	{ yTRACE(IVEC2); return IVEC2; }
ivec3/{LOOKAHEAD}	{ yTRACE(IVEC3); return IVEC3; }
ivec4/{LOOKAHEAD}	{ yTRACE(IVEC4); return IVEC4; }

float/{LOOKAHEAD}	{ yTRACE(FLOAT); return FLOAT; }
vec2/{LOOKAHEAD}	{ yTRACE(VEC2); return VEC2; }
vec3/{LOOKAHEAD}	{ yTRACE(VEC3); return VEC3; }
vec4/{LOOKAHEAD}	{ yTRACE(VEC4); return VEC4; }

const/{LOOKAHEAD}	{ yTRACE(CONST); return CONST; }

lit/{LOOKAHEAD}		{ yTRACE(LIT); return LIT; }
dp3/{LOOKAHEAD}		{ yTRACE(DP3); return DP3; }
rsq/{LOOKAHEAD}		{ yTRACE(RSQ); return RSQ; }

while/{LOOKAHEAD}	{ yTRACE(WHILE); return WHILE; }
void/{LOOKAHEAD}	{ yTRACE(VOID); return VOID; }

","		{ yTRACE(COMMA); return COMMA; }
";"		{ yTRACE(SEMI_COLUMN); return SEMI_COLUMN; }
"{"		{ yTRACE(LEFT_CBRACKET); return LEFT_CBRACKET; }
"}"		{ yTRACE(RIGHT_CBRACKET); return RIGHT_CBRACKET; }
"("		{ yTRACE(LEFT_BRACKET); return LEFT_BRACKET; }
")"		{ yTRACE(RIGHT_BRACKET); return RIGHT_BRACKET; }
"["		{ yTRACE(LEFT_SBRACKET); return LEFT_SBRACKET; }
"]"		{ yTRACE(RIGHT_SBRACKET); return RIGHT_SBRACKET; }
"!"		{ yTRACE(NOT); return NOT; } 
"*"		{ yTRACE(MULTI); return MULTI; }
"/"		{ yTRACE(DIVIDE); return DIVIDE; }
"+"		{ yTRACE(PLUS); return PLUS; }
"-"		{ yTRACE(MINUS); return MINUS; }
"<"		{ yTRACE(LESS); return LESS; }
"<="	{ yTRACE(LESS_EQUAL); return LESS_EQUAL; }
">" 	{ yTRACE(GREATER); return GREATER; }
">="	{ yTRACE(GREATER_EQUAL); return GREATER_EQUAL; }
"=="	{ yTRACE(DOUBLE_EQUAL); return DOUBLE_EQUAL; }
"!="	{ yTRACE(NOT_EQUAL); return NOT_EQUAL; }
"^"		{ yTRACE(EXP); return EXP; }
"&&"	{ yTRACE(LOGICAL_AND); return LOGICAL_AND; }
"||"	{ yTRACE(LOGICAL_OR); return LOGICAL_OR; }
"="		{ yTRACE(SINGLE_EQUAL); return SINGLE_EQUAL; }

"/*"	{ 
			int c;
			while ((c = yyinput()) != 0) {
				if (c == '\n') {
					yyline++;
				} else if (c == '*') {
					if ((c = yyinput()) == '/') {
						break;
					} else {
						unput(c);
					}
				}
			}

			if (c != '/') {
				yERROR("No closing comment found");
			}
		}

[A-Za-z_][A-Za-z0-9_]*/{LOOKAHEAD}	{
										if (yyleng <= MAX_IDENTIFIER) {
											yylval.as_id = (char *)malloc((yyleng + 1) * sizeof(char));
											if (yylval.as_id == NULL) {
												yERROR("Failed to allocate memory for identifier's name");								
											}

											strncpy(yylval.as_id, yytext, yyleng * sizeof(char));
											yTRACE(IDENTIFIER);
											return IDENTIFIER;
										} 
										yERROR("Choose another identifier name with length less than or equal to 32");	
									}

({INT_LIT})/{LOOKAHEAD}	{			
							char* ptr;
							int val = strtol(yytext, &ptr, 10);	
							if (abs(val) > MAX_INTEGER)	{
								yERROR("Integer's absolute value exceeds maximum value");					
							}
	
							yylval.as_int = val;
							yTRACE(INTEGER_LITERAL);
							return INTEGER_LITERAL;
							
						}

({FLT_LIT})/{LOOKAHEAD}	{
							char* ptr;
							double val = strtod(yytext, &ptr);
							if (fabs(val) > 1E+37) {
								yERROR("Float's absolute value exceeds its maximum value");
							}

							float valF = (float)val;
							yylval.as_float = valF;
							yTRACE(FLOAT_LITERAL);
							return FLOAT_LITERAL;
						}

(({INT_LIT}|{FLT_LIT})[Ee][+-]?{INT_LIT})/{LOOKAHEAD}	{
															char* ptr;
															double val = strtod(yytext, &ptr);
															if (fabs(val) > 1E+37) {
																yERROR("Float's absolute value exceeds its maximum value");
															}

															float valF = (float)val;
															yylval.as_float = valF;
															yTRACE(FLOAT_LITERAL);
															return FLOAT_LITERAL;
														}
\n		{ yyline++; }

{WS}+	{ /*do nothing*/ }

.		{ yERROR("Unknown token"); }

%%
