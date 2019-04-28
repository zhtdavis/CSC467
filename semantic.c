#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"
#include "common.h"
#include "symbol.h"

/*
LOGICAL_AND -> 0
LOGICAL_OR -> 1
DOUBLE_EQUAL -> 2
NOT_EQUAL -> 3
LESS -> 4
LESS_EQUAL -> 5
GREATER -> 6
GREATER_EQUAL -> 7
PLUS -> 8
MINUS -> 9
MULTI -> 10
DIVIDE -> 11
EXP -> 12
*/

/*
INT -> 0 
IVEC2 -> 1
IVEC3 -> 2
IVEC4 -> 3
BOOL -> 4
BVEC2 -> 5
BVEC3 -> 6
BVEC4 -> 7
FLOAT -> 8
VEC2 -> 9
VEC3 -> 10
VEC4 -> 11
*/


extern symbol_table_entry *curr_table_entry;

extern int scope_depth;

extern int errorOccurred;

extern bool if_else_scope;

extern bool in_assignment;

const char *get_type_str(int type_id);

const char *get_op_str(int op);


void print_error_message(char *error_message, int line_num) {
	fprintf(errorFile, "Line %d: %s", line_num, error_message);
	errorOccurred = 1;
}

/*
	traverse the arguments list for a function/constructor call
	return some string in the format of "0*0*"
*/
void arguments_list_traverse(node *curr, char *arguments) {
	if (curr == NULL) {
		return;	
	}
	arguments_list_traverse(curr->arguments.arguments_node, arguments);

	char argument[3];
	if (curr->arguments.expression_node != NULL) {
		sprintf(argument, "%d", curr->arguments.expression_node->type_id);
		strcat(arguments, argument);
		// add a dummy deliminater
		strcat(arguments, "*");
	}
}

/* 
	return 0 if normal variable
	return 1 if result variable
	return 2 if attribute variable
	return 3 if uniform variable
*/
int check_id_name(char *id_name) {
	// result
	if (strcmp(id_name, "gl_FragColor") == 0 ||
		strcmp(id_name, "gl_FragDepth") == 0) {
		return 1;	
	// attribute
	} else if (strcmp(id_name, "gl_FragCoord") == 0	||			
			   strcmp(id_name, "gl_TexCoord") == 0 ||
			   strcmp(id_name, "gl_Color") == 0 ||
			   strcmp(id_name, "gl_Secondary") == 0||
			   strcmp(id_name, "gl_FogFragCoord") == 0) {
		return 2;
	// uniform
	} else if (strcmp(id_name, "gl_Light_Half") == 0 ||
			   strcmp(id_name, "gl_Light_Ambient") == 0 || 
			   strcmp(id_name, "gl_Material_Shininess") == 0 ||
			   strcmp(id_name, "env1") == 0 || strcmp(id_name, "env2") == 0 || strcmp(id_name, "env3") == 0) {
		return 3;
	// normal
	} else {
		return 0;
	}
}

/*
	make sure const value is initialized with either literal value or uniform variable
*/
bool expression_node_traverse(node *curr) {
	if (curr == NULL) {
		return true;	
	}

	switch(curr->kind) {
		case CONSTRUCTOR_NODE:
			return expression_node_traverse(curr->constructor.arguments_node);
		case FUNCTION_NODE:
			return expression_node_traverse(curr->function.arguments_node);
		case INT_NODE:
			return true;
		case FLOAT_NODE:
			return true;
		case BOOL_NODE:
			return true;
		case EXPR_VAR_NODE:
			return expression_node_traverse(curr->expr_var.variable_node);
		case VAR_NODE: {
 			symbol_table_entry *entry = search_symbol_table(curr->var.id_name);
			if (check_id_name(curr->var.id_name) == 3 || (entry != NULL && entry->is_const)) {
				return true;			
			} else {
				return false;			
			}
		}
		case UNARY_EXPRESSION_NODE:
			return expression_node_traverse(curr->unary_expr.right);
		case BINARY_EXPRESSION_NODE:
			return expression_node_traverse(curr->binary_expr.left) && expression_node_traverse(curr->binary_expr.right);
		case NESTED_EXPRESSION_NODE:
			return expression_node_traverse(curr->nested_expression_node);
		case ARGUMENTS_NODE:
			return expression_node_traverse(curr->arguments.arguments_node) && expression_node_traverse(curr->arguments.expression_node);
		default:
			return false;
	}
}

/*
	boundry check
*/
bool is_valid_boundry(char *id_name, int type_id, int index, int line_num) {
	if (type_id == 0 || type_id == 4 || type_id == 8) {
		print_error_message(strdup("Accessing scalar with an index\n"), line_num);
		return false;
	} else if ((type_id == 1 || type_id == 5 || type_id == 9) && (index < 0 || index > 1)) {
		print_error_message(strdup("Accessing 2d vector with an invalid index\n"), line_num);
		return false;
	} else if ((type_id == 2 || type_id == 6 || type_id == 10) && (index < 0 || index > 2)) {
		print_error_message(strdup("Accessing 3d vector with an invalid index\n"), line_num);
		return false;
	} else if ((type_id == 3 || type_id == 7 || type_id == 11) && (index < 0 || index > 3)) {
		print_error_message(strdup("Accessing 4d vector with an invalid index\n"), line_num);
		return false;
	}
	return true;
}

bool is_same_base_type(int first, int second) {
	if (abs(first - second) <= 3) {
		return true;
	}
	return false;
}

bool is_same_size(int first, int second) {
	// since we have already checked that these two have the same base type
	return first == second;
}

int vector_size(int type_id) {
 	return type_id % 4 + 1;
}

bool is_bool_type(int type_id) {
	if (type_id == 4 || type_id == 5 || type_id == 6 || type_id == 7) {
		return true;	
	}
	return false;
}

bool is_arithmetic_type(int type_id) {
	return !is_bool_type(type_id);
}

void semantic_check(node *curr) {
	if (curr == NULL) {
		return;
	}

	switch(curr->kind) {
		case SCOPE_NODE: {
			// entering the scope
			scope_depth++;
			symbol_table_entry *save = curr_table_entry;
			
			semantic_check(curr->scope.declarations_node);
			semantic_check(curr->scope.statements_node);
	
			// leaving the scope
			scope_depth--;
			curr_table_entry = save;
		}
		break;
		case UNARY_EXPRESSION_NODE: {
			semantic_check(curr->unary_expr.right);
			
			int type_id = curr->unary_expr.right->type_id;
			// -
			if (curr->unary_expr.op == '-') {
				if (!is_arithmetic_type(type_id)) {
					print_error_message(strdup("All operands to arithmetic operators(-) must have arithmetic types\n"), curr->line_num);
					curr->type_id = -1;
					return;
				}
				curr->type_id = type_id;
			// !
			} else {
				if (!is_bool_type(type_id)) {
					print_error_message(strdup("All operands to logical operators(!) must have boolean types\n"), curr->line_num);
					curr->type_id = -1;
					return;
				}
				curr->type_id = type_id;
			}
		}
		break;
		case BINARY_EXPRESSION_NODE: {
			semantic_check(curr->binary_expr.left);
			semantic_check(curr->binary_expr.right);

			int left_type = curr->binary_expr.left->type_id;
			int right_type = curr->binary_expr.right->type_id;

			// one of the operand is invalid, no need to proceed the expression evaluation
			if (left_type == -1 || right_type == -1) {
				curr->type_id = -1;
				return;
			}
			
			// binary operation can only be performed between operand of the same base type;
			if (!is_same_base_type(left_type, right_type)) {
				print_error_message(strdup("Binary operation between operands with different base type\n"), curr->line_num);
				curr->type_id = -1;
				return;
			}
			
			int op = curr->binary_expr.op;
			// &&, ||
			if (op == 0 || op == 1) {
				if (!is_same_size(left_type, right_type)) {
					print_error_message(strdup("Binary operation && || between operands with different sizes\n"), curr->line_num);
					curr->type_id = -1;
					return;			
				} else if (!is_bool_type(left_type) || !is_bool_type(right_type)) {
					print_error_message(strdup("All operands to logical operators(&& ||) must have boolean types\n"), curr->line_num);
					curr->type_id = -1;
					return;
				}
				curr->type_id = left_type;
			// +, -
			} else if (op == 8 || op == 9) {
				if (!is_same_size(left_type, right_type)) {
					print_error_message(strdup("Arithmetic operation + - between operands with different sizes\n"), curr->line_num);
					curr->type_id = -1;
					return;			
				} else if (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type)) {
					print_error_message(strdup("All operands to arithmetic operators(+ -) must have arithmetic types\n"), curr->line_num);
					curr->type_id = -1;
					return;				
				}
				curr->type_id = left_type;
			// /, ^
			} else if (op == 11 || op == 12) {
				if (vector_size(left_type) != 1 || vector_size(right_type) != 1) {
					print_error_message(strdup("Arithmetic operation / ^ between operands with size larger than 1\n"), curr->line_num);
					curr->type_id = -1;
					return;
				} else if (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type)) {
					print_error_message(strdup("All operands to arithmetic operators(/ ^) must have arithmetic types\n"), curr->line_num);
					curr->type_id = -1;
					return;				
				}
				curr->type_id = left_type;
			// <, <=, >, >=
			} else if (op == 4 || op == 5 || op == 6 || op == 7) {
				if (vector_size(left_type) != 1 || vector_size(right_type) != 1) {
					print_error_message(strdup("Comparison operation < <= > >= between operands with size larger than 1\n"), curr->line_num);
					curr->type_id = -1;
					return;
				} else if (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type)) {
					print_error_message(strdup("All operands to comparison operators(< <= > >=) must have arithmetic types\n"), curr->line_num);
					curr->type_id = -1;
					return;				
				}
				curr->type_id = 4;
			// ==, !=
			} else if (op == 2 || op == 3) {
				if (!is_same_size(left_type, right_type)) {
					print_error_message(strdup("Comparison operation == != between operands with different sizes\n"), curr->line_num);
					curr->type_id = -1;
					return;			
				} else if (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type)) {
					print_error_message(strdup("All operands to comparison operators(== !=) must have arithmetic types\n"), curr->line_num);
					curr->type_id = -1;
					return;				
				}
				curr->type_id = 4;
			// *
			} else if (op == 10) {
				if (!is_arithmetic_type(left_type) || !is_arithmetic_type(right_type)) {
					print_error_message(strdup("All operands to arithmetic operators(*) must have arithmetic types\n"), curr->line_num);
					curr->type_id = -1;
					return;				
				// scalar*scalar
				} else if (vector_size(left_type) == 1 && vector_size(right_type) == 1) {
					curr->type_id = left_type;
				// vector*vector
				} else if (vector_size(left_type) > 1 && vector_size(right_type) > 1) {
					if (!is_same_size(left_type, right_type)) {
						print_error_message(strdup("Arithmetic operation * between vector operands with different sizes\n"), curr->line_num);
						curr->type_id = -1;
						return;
					}
					curr->type_id = left_type;
				// scalar*vector or vector*scalar
				} else if (vector_size(left_type) == 1 || vector_size(right_type) == 1) {
					curr->type_id = left_type > right_type ? left_type : right_type; 
				}
			}
		}
		break;
		case INT_NODE:
			curr->type_id = 0;
		break;
		case FLOAT_NODE:
			curr->type_id = 8;
		break;
		case VAR_NODE: {
			symbol_table_entry *entry = search_symbol_table(curr->var.id_name);
			if (entry == NULL) {
				print_error_message(strdup("Identifier undeclared\n"), curr->line_num);
				curr->type_id = -1;
				return;
			}

			// reading a result variable
			if (!in_assignment && check_id_name(curr->var.id_name) == 1) {
				print_error_message(strdup("Result variable is write only\n"), curr->line_num);
				curr->type_id = -1;
				return;
			}				
			
			int type_id = entry->type_id;
			// not accessing through random access operator[]
			if (curr->var.index == -1) {
				curr->type_id = type_id;
			} else if (!is_valid_boundry(curr->var.id_name, type_id, curr->var.index, curr->line_num)) {
				curr->type_id = -1;
			// ivec2 a; a[0];
			} else if (type_id == 1 || type_id == 2 || type_id == 3) {
				curr->type_id = 0;
			// bvec2 a; a[0];
			} else if (type_id == 5 || type_id == 6 || type_id == 7) {
				curr->type_id = 4;
			// vec2 a; a[0];
			} else if (type_id == 9 || type_id == 10 || type_id == 11) {
				curr->type_id = 8;				
			}	
		}
		break;
		case FUNCTION_NODE:
			semantic_check(curr->function.arguments_node);
			char arguments[50];
			arguments[0] = '\0';
			arguments_list_traverse(curr->function.arguments_node, arguments);
			
			// dp3
			if (curr->function.function_id == 0) {
				if (strcmp(arguments, "11*11*") != 0 &&
					strcmp(arguments, "10*10*") != 0 && 
					strcmp(arguments, "3*3*") != 0 &&
					strcmp(arguments, "2*2*") != 0) {
					print_error_message(strdup("Invalid arguments list for dp3\n"), curr->line_num);
					curr->type_id = -1;
					return;
				}
				curr->type_id = 8;
			// lit
			} else if (curr->function.function_id == 1) {
				if (strcmp(arguments, "11*") != 0) {
					print_error_message(strdup("Invalid arguments list for lit\n"), curr->line_num);
					curr->type_id = -1;
					return;
				}
				curr->type_id = 11;
			// rsq
			} else {
				if (strcmp(arguments, "8*") != 0 && strcmp(arguments, "0*") != 0) {
					print_error_message(strdup("Invalid arguments list for rsq\n"), curr->line_num);
					curr->type_id = -1;
					return;
				}
				curr->type_id = 8;
			}
		break;
		case CONSTRUCTOR_NODE: {
			semantic_check(curr->constructor.type_node);
			semantic_check(curr->constructor.arguments_node);

			char arguments[50];
			arguments[0] = '\0';
			arguments_list_traverse(curr->constructor.arguments_node, arguments);
			
			// make sure arguments list matches
			int type_id = curr->constructor.type_node->type_id;
			if ((type_id == 0 && strcmp(arguments, "0*") != 0) ||
				(type_id == 1 && strcmp(arguments, "0*0*") != 0) ||
				(type_id == 2 && strcmp(arguments, "0*0*0*") != 0) || 	
				(type_id == 3 && strcmp(arguments, "0*0*0*0*") != 0) || 
				(type_id == 4 && strcmp(arguments, "4*") != 0) ||
				(type_id == 5 && strcmp(arguments, "4*4*") != 0) || 
				(type_id == 6 && strcmp(arguments, "4*4*4*") != 0) ||
				(type_id == 7 && strcmp(arguments, "4*4*4*4*") != 0) ||
				(type_id == 8 && strcmp(arguments, "8*") != 0) ||
				(type_id == 9 && strcmp(arguments, "8*8*") != 0) ||
				(type_id == 10 && strcmp(arguments, "8*8*8*") != 0) ||
				(type_id == 11 && strcmp(arguments, "8*8*8*8*") != 0)) {
				print_error_message(strdup("Invalid arguments list for constructor call\n"), curr->line_num);
				curr->type_id = -1;
				return;
			}  
			curr->type_id = type_id;
		}
		break;
		case IF_STATEMENT_NODE: {
			semantic_check(curr->if_statement.condition_node);
			if (curr->if_statement.condition_node->type_id != 4 && 
				curr->if_statement.condition_node->type_id != -1) {
				print_error_message(strdup("If condition does not return bool\n"), curr->if_statement.condition_node->line_num);
			}
			
			symbol_table_entry *save = curr_table_entry;

			// entering if scope
			scope_depth++;
			if_else_scope = true;
			semantic_check(curr->if_statement.if_node);
			// leaving if scope
			if_else_scope = false;
			scope_depth--;
			curr_table_entry = save;
			

			// entering else scope
			scope_depth++;
			if_else_scope = true;
			semantic_check(curr->if_statement.else_node);
			// leaving else scope
			if_else_scope = false;
			scope_depth--;
			curr_table_entry = save;
		}
		break;
		case ASSIGNMENT_NODE: {
			// probably not a good flag name to choose...	
			// result variable can only appear on LHS of assignment statement
			in_assignment = true;
			semantic_check(curr->assignment.variable_node);
			in_assignment = false;

			semantic_check(curr->assignment.expression_node);

			char *id_name = curr->assignment.variable_node->var.id_name;
			// result
			if (check_id_name(id_name) == 1 && if_else_scope) {
				print_error_message(strdup("Result variable cannot be assigned in if/else scope\n"), curr->line_num);
			// attribute
			} else if (check_id_name(id_name) == 2) {
				print_error_message(strdup("Attribute variable is read-only\n"), curr->line_num);
			// uniform
			} else if (check_id_name(id_name) == 3) {
				print_error_message(strdup("Uniform variable is read-only\n"), curr->line_num);
			}
		
			symbol_table_entry *entry = search_symbol_table(id_name);
			if (entry != NULL && entry->is_const && check_id_name(id_name) == 0) {
				print_error_message(strdup("Cannot assign value to const variable\n"), curr->line_num);
			}

			// make sure LHS and RHS type match
			int left_type = curr->assignment.variable_node->type_id;
			int right_type = curr->assignment.expression_node->type_id;
			if (left_type != -1 && right_type != -1 && left_type != right_type) {
				print_error_message(strdup("LHS and RHS do not match in type\n"), curr->line_num);
			}
		}
		break;
		case NESTED_SCOPE_NODE:
			semantic_check(curr->nested_scope_node);
		break;
		case STATEMENTS_NODE:
			semantic_check(curr->statements.statements_node);
			semantic_check(curr->statements.statement_node);
		break;
		case ARGUMENTS_NODE:
			semantic_check(curr->arguments.arguments_node);
			semantic_check(curr->arguments.expression_node);
		break;
		case TYPE_NODE:
		/* Do Nothing */
		break;
		case BOOL_NODE:
			curr->type_id = 4;
		break;		
		case DECLARATION_NODE: {
			semantic_check(curr->declaration.type_node);
			semantic_check(curr->declaration.expression_node);
			
			// check if the variable name has conflict with pre-defined variable
			char *id_name = curr->declaration.id_name;
			if (check_id_name(id_name) >= 1) {
				print_error_message(strdup("Conflict name with pre-defined variable\n"), curr->line_num);
				return;
			}
			
			// check if the variable name has already been declared in current scope
			if (check_pre_existing_symbol(id_name)) {
				print_error_message(strdup("Duplicate variable name in the same scope\n"), curr->line_num);
				return;
			}

			// check if the LHS and RHS have the same type, no implicit conversion
			// still need to push the varibale onto the symbol table
			int var_type = curr->declaration.type_node->type_id;
			if (curr->declaration.expression_node != NULL && 
				curr->declaration.expression_node->type_id != var_type &&
				curr->declaration.expression_node->type_id != -1) {
				print_error_message(strdup("LHS and RHS do not match in type\n"), curr->line_num);
				//return;
			}

			if (curr->declaration.is_const && 
				!expression_node_traverse(curr->declaration.expression_node) &&
				curr->declaration.expression_node->type_id != -1) {
				print_error_message(strdup("Const qualified variables must be initialized with a literal value or with a uniform variable\n"), curr->line_num);
			}

			// add new symbol table entry
			add_new_entry(curr->declaration.is_const, curr->declaration.type_node->type_id, scope_depth, id_name);
		}
		break;
		case DECLARATIONS_NODE:
			semantic_check(curr->declarations.declarations_node);
			semantic_check(curr->declarations.declaration_node);
		break;
		case EXPR_VAR_NODE:
			semantic_check(curr->expr_var.variable_node);
			curr->type_id = curr->expr_var.variable_node->type_id;
		break;
		case NESTED_EXPRESSION_NODE:
			semantic_check(curr->nested_expression_node);
			curr->type_id = curr->nested_expression_node->type_id;
		break;
		default:
		break;
	}
}
