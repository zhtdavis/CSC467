#ifndef CODEGEN_H_
#define CODEGEN_H_ 1

#include "ast.h"

typedef enum {
	ABS,
	ADD,
	COS,
	CMP,
	DP3,
	DP4,
	DPH,
	FLR,
	FRC,
	KIL,
	LG2,
	LIT,
	LRP,
	MAD,
	MAX,
	MIN,
	MOV,
	MUL,
	POW,
	RCP,
	RSQ,
	SCS,
	SGE,
	SIN,
	SLT,
	SUB,
	SWZ,
	TEX,
	TXB,
	TXP,
	XPD
} op_kind;

typedef struct instruction_ {
	bool is_declaration;
	op_kind op;	
	char *in1, *in2, *in3;
	char *out;
	struct instruction_ *next;
} instruction;

void genCode(node *curr);
void print_result();

#endif
