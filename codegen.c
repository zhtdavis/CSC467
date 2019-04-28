#include "codegen.h"
#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

instruction *curr_instruction = NULL;

instruction *head_instruction = NULL;

int temp_reg_count = 0;

char *if_condition = NULL;

void add_instruction(bool is_declaration, 
					 op_kind op,
					 char *in1,
					 char *in2,
					 char *in3,
					 char *out) {
	instruction *temp = (instruction *)malloc(sizeof(instruction));
	temp->is_declaration = is_declaration;
	temp->op = op;
	temp->in1 = in1;
	temp->in2 = in2;
	temp->in3 = in3;
	temp->out = out;

	if (curr_instruction) {
		curr_instruction->next = temp;	
	} else {
		head_instruction = temp;
	}
	curr_instruction = temp;
}

void add_instruction(char *str) {

}

char *get_op_str(op_kind op) {
	switch(op) {
		case ABS:
		return "ABS";
		case ADD:
		return "ADD";
		case COS:
		return "COS";
		case CMP:
		return "CMP";
		case DP3:
		return "DP3";
		case DP4:
		return "DP4";
		case DPH:
		return "DPH";
		case FLR:
		return "FLR";
		case FRC:
		return "FRC";
		case KIL:
		return "KIL";
		case LG2:
		return "LG2";
		case LIT:
		return "LIT";
		case LRP:
		return "LRP";
		case MAD:
		return "MAD";
		case MAX:
		return "MAX";
		case MIN:
		return "MIN";
		case MOV:
		return "MOV";
		case MUL:
		return "MUL";
		case POW: 
		return "POW";
		case RCP:
		return "RCP";
		case RSQ:
		return "RSQ";
		case SCS:
		return "SCS";
		case SGE:
		return "SGE";
		case SIN:
		return "SIN";
		case SLT:
		return "SLT";
		case SUB:
		return "SUB";
		case SWZ:
		return "SWZ";
		case TEX:
		return "TEX";
		case TXB:
		return "TXB";
		case TXP:
		return "TXP";
		case XPD:
		return "XPD";
		default:
		return "";
	}
}

void print_instruction(instruction *curr) {
	char *str = (char *)calloc(100, sizeof(char));
	if (curr->is_declaration) {
		snprintf(str, 100, "TEMP %s;", curr->out);
	} else {
		if (curr->in1 && curr->in2 && curr->in3 && curr->out) {
			snprintf(str, 100, "%s %s,%s,%s,%s;", 
					 get_op_str(curr->op), 
					 curr->out, curr->in1, 
					 curr->in2, curr->in3);
		} else if (curr->in1 && curr->in2 && curr->out) {
			snprintf(str, 100, "%s %s,%s,%s;", 
					 get_op_str(curr->op), 
					 curr->out, curr->in1, 
					 curr->in2);	
		} else if (curr->in1 && curr->out) {
			snprintf(str, 100, "%s %s,%s;", 
					 get_op_str(curr->op), 
					 curr->out, curr->in1);	
		}
	}
	fprintf(outputFile, "%s\n", str);
}

char *get_temp_reg() {
	char *str = (char *)calloc(10, sizeof(char));
	snprintf(str, 20, "temp_var_%d", temp_reg_count++);
	return str;
}

static void arguments_list_traverse(node *curr, char *arguments) {
	if (!curr) {
		return;	
	}

	arguments_list_traverse(curr->arguments.arguments_node, arguments);
	if (curr->arguments.expression_node) {
		strcat(arguments, curr->arguments.expression_node->temp_var_name);
		strcat(arguments, ",");
	}
}

void genCode(node *curr) {
	if (!curr) {
		return;		
	}

	switch(curr->kind) {
		case SCOPE_NODE:
			genCode(curr->scope.declarations_node);
			genCode(curr->scope.statements_node);
		break;
		case UNARY_EXPRESSION_NODE: {
			genCode(curr->unary_expr.right);
			char *temp_reg = get_temp_reg();
			add_instruction(true, ADD, NULL,
							NULL, NULL, temp_reg);
			if (curr->unary_expr.op == '-') {
				add_instruction(false, SUB, "{0.0, 0.0, 0.0, 0.0}",
								curr->unary_expr.right->temp_var_name, NULL, temp_reg);
			} else {
				add_instruction(false, SUB, "{1.0, 1.0, 1.0, 1.0}",
								curr->unary_expr.right->temp_var_name, NULL, temp_reg);
			}

			curr->temp_var_name = temp_reg;
			break;
		}
		case BINARY_EXPRESSION_NODE: {
			genCode(curr->binary_expr.left);
			genCode(curr->binary_expr.right);
			
			char *temp_reg = get_temp_reg();
			add_instruction(true, ADD, NULL,
							NULL, NULL, temp_reg);
			char *left = curr->binary_expr.left->temp_var_name;
			char *right = curr->binary_expr.right->temp_var_name;

			int op = curr->binary_expr.op;
			// && 	x*y			
			if (op == 0) {
				add_instruction(false, MUL, left,
								right, NULL, temp_reg);
			// || 	x+y - x*y
			} else if (op == 1) {
				add_instruction(false, MUL, left,
								right, NULL, temp_reg);
				add_instruction(false, SUB, right,
								temp_reg, NULL, temp_reg);
				add_instruction(false, ADD, left,
								temp_reg, NULL, temp_reg);
			// == 	(x-y)>=0 *(y-x)>=0
			} else if (op == 2) {
				add_instruction(false, SUB, left, 
								right, NULL, temp_reg);
				char *temp_reg2 = get_temp_reg();
				add_instruction(true, ADD, NULL,
								NULL, NULL, temp_reg2);
				add_instruction(false, SUB, right, 
								left, NULL, temp_reg2);
				add_instruction(false, CMP, temp_reg, 
								"{0.0, 0.0, 0.0, 0.0}", "{1.0, 1.0, 1.0, 1.0}", temp_reg);
				add_instruction(false, CMP, temp_reg2, 
								"{0.0, 0.0, 0.0, 0.0}", "{1.0, 1.0, 1.0, 1.0}", temp_reg2);
				add_instruction(false, MUL, temp_reg,
								temp_reg2, NULL, temp_reg);
			// != 	(x-y)<0 + (y-x)<0
			} else if (op == 3) {
				add_instruction(false, SUB, left, 
								right, NULL, temp_reg);
				char *temp_reg2 = get_temp_reg();
				add_instruction(true, ADD, NULL,
								NULL, NULL, temp_reg2);
				add_instruction(false, SUB, right, 
								left, NULL, temp_reg2);
				add_instruction(false, CMP, temp_reg, 
								"{1.0, 1.0, 1.0, 1.0}", "{0.0, 0.0, 0.0, 0.0}", temp_reg);
				add_instruction(false, CMP, temp_reg2, 
								"{1.0, 1.0, 1.0, 1.0}", "{0.0, 0.0, 0.0, 0.0}", temp_reg2);
				add_instruction(false, ADD, temp_reg,
								temp_reg2, NULL, temp_reg);
			// < 	x-y < 0
			} else if (op == 4) {
				add_instruction(false, SUB, left,
								right, NULL, temp_reg);
				add_instruction(false, CMP, temp_reg,
								"{1.0, 1.0, 1.0, 1.0}", "{0.0, 0.0, 0.0, 0.0}", temp_reg);
			// <= 	y-x >= 0	
			} else if (op == 5) {
				add_instruction(false, SUB, right, 
								left, NULL, temp_reg);
				add_instruction(false, CMP, temp_reg,
								"{0.0, 0.0, 0.0, 0.0}", "{1.0, 1.0, 1.0, 1.0}", temp_reg);
			// > 	y-x < 0
			} else if (op == 6) {
				add_instruction(false, SUB, right, 
								left, NULL, temp_reg);
				add_instruction(false, CMP, temp_reg,
								"{1.0, 1.0, 1.0, 1.0}", "{0.0, 0.0, 0.0, 0.0}", temp_reg);
			// >= 	x-y >= 0
			} else if (op == 7) {
				add_instruction(false, SUB, left,
								right, NULL, temp_reg);
				add_instruction(false, CMP, temp_reg,
								"{0.0, 0.0, 0.0, 0.0}", "{1.0, 1.0, 1.0, 1.0}", temp_reg);
			// + 
			} else if (op == 8) {
				add_instruction(false, ADD, left,
								right, NULL, temp_reg);
			// -
			} else if (op == 9) {
				add_instruction(false, SUB, left,
								right, NULL, temp_reg);
			// *
			} else if (op == 10) {
				add_instruction(false, MUL, left,
								right, NULL, temp_reg);	
			// /		
			} else if (op == 11) {
				add_instruction(false, RCP, right,
								NULL, NULL, temp_reg);
				add_instruction(false, MUL, left,
								temp_reg, NULL, temp_reg);
				if (curr->binary_expr.left->kind == INT_NODE && curr->binary_expr.right->kind == INT_NODE) {
					add_instruction(false, FLR, temp_reg,
									NULL, NULL, temp_reg);
				}
			// ^
			} else if (op == 12) {
				add_instruction(false, POW, left,
								right, NULL, temp_reg);
			}

			curr->temp_var_name = temp_reg;
			break;
		}
		case INT_NODE: {
			char *str = (char *)calloc(10, sizeof(char));
			snprintf(str, 10, "%.1f", (float)curr->int_val);
			curr->temp_var_name = str;
			break;
		}
		case FLOAT_NODE: {
			char *str = (char *)calloc(10, sizeof(char));
			snprintf(str, 10, "%.1f", curr->float_val);
			curr->temp_var_name = str;
			break;
		}
		case VAR_NODE: {
			char *str = (char *)calloc(50, sizeof(char));
			if (strcmp(curr->var.id_name, "gl_FragColor") == 0) {
				snprintf(str, 50, "result.color");		
			} else if (strcmp(curr->var.id_name, "gl_FragDepth") == 0) {
				snprintf(str, 50, "result.depth");		
			} else if (strcmp(curr->var.id_name, "gl_FragCoord") == 0) {
				snprintf(str, 50, "fragment.position");
			} else if (strcmp(curr->var.id_name, "gl_TexCoord") == 0) {
				snprintf(str, 50, "fragment.texcoord");			
			} else if (strcmp(curr->var.id_name, "gl_Color") == 0) {
				snprintf(str, 50, "fragment.color");		
			} else if (strcmp(curr->var.id_name, "gl_Secondary") == 0) {
				snprintf(str, 50, "fragment.color.secondary");			
			} else if (strcmp(curr->var.id_name, "gl_FogFragCoord") == 0) {
				snprintf(str, 50, "fragment.fogcoord");			
			} else if (strcmp(curr->var.id_name, "gl_Light_Half") == 0) {
				snprintf(str, 50, "state.light[0].half");
			} else if (strcmp(curr->var.id_name, "gl_Light_Ambient") == 0) {
				snprintf(str, 50, "state.lightmodel.ambient");			
			} else if (strcmp(curr->var.id_name, "gl_Material_Shininess") == 0) {
				snprintf(str, 50, "state.material.shininess");			
			} else if (strcmp(curr->var.id_name, "env1") == 0) {
				snprintf(str, 50, "program.env[1]");
			} else if (strcmp(curr->var.id_name, "env2") == 0) {
				snprintf(str, 50, "program.env[2]");
			} else if (strcmp(curr->var.id_name, "env3") == 0) {
				snprintf(str, 50, "program.env[3]");
			} else {
				snprintf(str, 50, curr->var.id_name);			
			}

			if (curr->var.index == -1) {
				// pass
			} else if (curr->var.index == 0) {
				strcat(str, ".x");
			} else if (curr->var.index == 1) {
				strcat(str, ".y");			
			} else if (curr->var.index == 2) {
				strcat(str, ".z");			
			} else if (curr->var.index == 3) {
				strcat(str, ".w");			
			}
			
			curr->temp_var_name = str;			
			break;
		}
		case FUNCTION_NODE: {
			genCode(curr->function.arguments_node);
			char *temp_reg = get_temp_reg();
			add_instruction(true, ADD, NULL, 
							NULL, NULL, temp_reg);
	
			char *arguments = (char *)calloc(30, sizeof(char));
			arguments_list_traverse(curr->constructor.arguments_node, arguments);
			
			if (curr->function.function_id == 0) {
				char *in1, *in2;
				in1 = strtok(arguments, ",");
				in2 = strtok(NULL, ",");
				add_instruction(false, DP3, in1,
								in2, NULL, temp_reg);
			} else if (curr->function.function_id == 1) {
				char *in1 = strtok(arguments, ",");
				add_instruction(false, LIT, in1,
								NULL, NULL, temp_reg);
 			} else {
				char *in1 = strtok(arguments, ",");
				add_instruction(false, RSQ, in1,
								NULL, NULL, temp_reg);
			}
			
			curr->temp_var_name = temp_reg;	
			break;
		}
		case CONSTRUCTOR_NODE: {
			genCode(curr->constructor.type_node);
			genCode(curr->constructor.arguments_node);
			char *arguments = (char *)calloc(30, sizeof(char));
			strcat(arguments, "{");
			arguments_list_traverse(curr->constructor.arguments_node, arguments);
			arguments[strlen(arguments)-1] = '\0';
			strcat(arguments, "}");
			curr->temp_var_name = arguments;
			break;
		}
		case IF_STATEMENT_NODE: {
			genCode(curr->if_statement.condition_node);
			if_condition = curr->if_statement.condition_node->temp_var_name;
			char *save = get_temp_reg();
			add_instruction(true, ADD, NULL,
							NULL, NULL, save);
			add_instruction(false, MOV, if_condition,
						 	NULL, NULL, save);

			// enter if statement
			add_instruction(false, SUB, "{0.0, 0.0, 0.0, 0.0}",
							if_condition, NULL, if_condition);
			genCode(curr->if_statement.if_node);
			
			// enter else node
			add_instruction(false, MOV, save,
							NULL, NULL, if_condition);
			add_instruction(false, SUB, if_condition, 
							"{1.0, 1.0, 1.0, 1.0}", NULL, if_condition);
			genCode(curr->if_statement.else_node);
			
			// leave if/else node
			if_condition = NULL;
			break;
		}
		case ASSIGNMENT_NODE: {
			genCode(curr->assignment.variable_node);
			genCode(curr->assignment.expression_node);
			
			char *left = curr->assignment.variable_node->temp_var_name;
			char *right = curr->assignment.expression_node->temp_var_name;
			
			if (if_condition) {
				add_instruction(false, CMP, if_condition,
								right, left, left);	
			} else {
				add_instruction(false, MOV, right,
								NULL, NULL, left);
			}		
			break;
		}
		case NESTED_SCOPE_NODE:
			genCode(curr->nested_scope_node);
		break;
		case STATEMENTS_NODE:
			genCode(curr->statements.statements_node);
			genCode(curr->statements.statement_node);
		break;
		case ARGUMENTS_NODE:
			genCode(curr->arguments.arguments_node);
			genCode(curr->arguments.expression_node);
		break;
		case TYPE_NODE:
		/*Do Nothing*/
		break;
		case BOOL_NODE: {
			char *temp_reg = get_temp_reg();
			add_instruction(true, ADD, NULL,
							NULL, NULL, temp_reg);

			char *str = (char *)calloc(30, sizeof(char));
			snprintf(str, 30, "{%.1f, %.1f, %.1f, %.1f}", 
					 (float)curr->bool_val, 
					 (float)curr->bool_val,
					 (float)curr->bool_val,
					 (float)curr->bool_val);

			add_instruction(false, MOV, str, 
							NULL, NULL, temp_reg);
			curr->temp_var_name = temp_reg;
			break;
		}
		case DECLARATION_NODE:
			genCode(curr->declaration.type_node);
			genCode(curr->declaration.expression_node);
			add_instruction(true, ADD, 
							NULL, NULL, 
							NULL, curr->declaration.id_name);
			if (curr->declaration.expression_node) {
				add_instruction(false, MOV, curr->declaration.expression_node->temp_var_name,
								NULL, NULL, curr->declaration.id_name);
			}
		break;
		case DECLARATIONS_NODE:
			genCode(curr->declarations.declarations_node);
			genCode(curr->declarations.declaration_node);
		break;
		case EXPR_VAR_NODE:
			genCode(curr->expr_var.variable_node);
			curr->temp_var_name = curr->expr_var.variable_node->temp_var_name;
		break;
		case NESTED_EXPRESSION_NODE:
			genCode(curr->nested_expression_node);
		break;
		default:
		break;
	}
}

void print_result() {
	fprintf(outputFile, "!!ARBfp1.0\n");
	instruction *curr = head_instruction;
	while (curr) {
		print_instruction(curr);
		curr = curr->next;
	}
	fprintf(outputFile, "END\n");
}
