#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

#include "ast.h"
#include "common.h"
#include "parser.tab.h"
#include "symbol.h"

#define DEBUG_PRINT_TREE 0

node *ast = NULL;

symbol_table_entry *curr_table_entry = NULL;

int scope_depth = 0;

bool if_else_scope = false;

bool in_assignment = false;

node *ast_allocate(node_kind kind, ...) {
  va_list args;

  // make the node
  node *ast = (node *) malloc(sizeof(node));
  memset(ast, 0, sizeof *ast);
  ast->kind = kind;

  va_start(args, kind); 

  switch(kind) {

  case SCOPE_NODE:
	ast->scope.declarations_node = va_arg(args, node *);
	ast->scope.statements_node = va_arg(args, node *);
	break;
  case UNARY_EXPRESSION_NODE:
	ast->unary_expr.op = va_arg(args, int);
	ast->unary_expr.right = va_arg(args, node *);
	ast->line_num = va_arg(args, int);
	// ast->type_id = ast->unary_expr.right->type_id;
	break;
  case BINARY_EXPRESSION_NODE:
    ast->binary_expr.op = va_arg(args, int);
    ast->binary_expr.left = va_arg(args, node *);
    ast->binary_expr.right = va_arg(args, node *); 
	ast->line_num = va_arg(args, int);
	// ast->type_id = ast->binary_expr.left->type_id;
    break;
  case INT_NODE:
	ast->int_val = va_arg(args, int);
	ast->line_num = va_arg(args, int);
	// ast->type_id = 0;
	break;
  case FLOAT_NODE:
	ast->float_val = va_arg(args, double);
	ast->line_num = va_arg(args, int);
	//ast->type_id = 8;
	break;
  case VAR_NODE:
	ast->var.id_name = va_arg(args, char *);
	ast->var.index = va_arg(args, int);
	ast->line_num = va_arg(args, int);
	break;
  case FUNCTION_NODE:
	ast->function.function_id = va_arg(args, int);
	ast->function.arguments_node = va_arg(args, node *);
	ast->line_num = va_arg(args, int);
	break;
  case CONSTRUCTOR_NODE:
	ast->constructor.type_node = va_arg(args, node *);
	ast->constructor.arguments_node = va_arg(args, node *);
	ast->line_num = va_arg(args, int);
	// ast->type_id = ast->constructor.type_node->type_id;
	break;
  case IF_STATEMENT_NODE:
	ast->if_statement.condition_node = va_arg(args, node *);
	ast->if_statement.if_node = va_arg(args, node *);
	ast->if_statement.else_node = va_arg(args, node *);
	break;
  case ASSIGNMENT_NODE:
	ast->assignment.variable_node = va_arg(args, node *);
	ast->assignment.expression_node = va_arg(args, node *);
	ast->line_num = va_arg(args, int);
	break;
  case NESTED_SCOPE_NODE:
	ast->nested_scope_node = va_arg(args, node *);
	break;
  case STATEMENTS_NODE:
	ast->statements.statements_node = va_arg(args, node *);
	ast->statements.statement_node = va_arg(args, node *); 
	break;
  case ARGUMENTS_NODE:
	ast->arguments.arguments_node = va_arg(args, node *);
	ast->arguments.expression_node = va_arg(args, node *);
	break;
  case TYPE_NODE:
	ast->type_id = va_arg(args, int);
	break;
  case BOOL_NODE:
	ast->bool_val = va_arg(args, int);
	ast->line_num = va_arg(args, int);
	break;
  case DECLARATION_NODE:
	ast->declaration.is_const = va_arg(args, int);
	ast->declaration.type_node = va_arg(args, node *);
	ast->declaration.id_name = va_arg(args, char *);
	ast->declaration.expression_node = va_arg(args, node *);
	ast->line_num = va_arg(args, int);
	break;
  case DECLARATIONS_NODE:
	ast->declarations.declarations_node = va_arg(args, node *);
	ast->declarations.declaration_node = va_arg(args, node *);
	break;
  case EXPR_VAR_NODE:
	ast->expr_var.variable_node = va_arg(args, node *);
	ast->line_num = va_arg(args, int);
	break;
  case NESTED_EXPRESSION_NODE:
	ast->nested_expression_node = va_arg(args, node *);
	break;
  default: 
	break;
  }

  va_end(args);

  return ast;
}

void print_indent(int depth, int is_open, int new_line) {
	if (new_line) {
		fprintf(dumpFile, "\n");
		for (int i = 0; i < depth; i++) {
			fprintf(dumpFile, "  ");	
		}
	}
	fprintf(dumpFile, is_open ? "(" : ")");
}

const char *get_op_str(int op) {
	switch(op) {
		case '!':
			return "!";
		case '-':
			return "-";
		case 0:
			return "&&";
		case 1:
			return "||";
		case 2:
			return "==";
		case 3:
			return "!=";
		case 4:
			return "<";
		case 5:
			return "<=";
		case 6:
			return ">";
		case 7:
			return ">=";
		case 8:
			return "+";
		case 9:
			return "-";
		case 10:
			return "*";
		case 11:
			return "/";
		case 12:
			return "^";
		default:
			return "";
	}
}

const char *get_type_str(int type_id) {
	switch(type_id) {
		case 0:
			return "INT";
		case 1:
			return "IVEV2";
		case 2:
			return "IVEC3";
		case 3:
			return "IVEC4";
		case 4:
			return "BOOL";
		case 5:
			return "BVEC2";
		case 6:
			return "BVEC3";
		case 7:
			return "BVEC4";
		case 8:
			return "FLOAT";
		case 9:
			return "VEC2";
		case 10:
			return "VEC3";
		case 11:
			return "VEC4";
		default:
			return "Any";
	}
}

void ast_print_helper(node *curr, int depth) {
	if (curr == NULL) {
		return;	
	}

	switch(curr->kind) {
		case SCOPE_NODE:
			print_indent(depth, 1, 1);
			fprintf(dumpFile, "SCOPE ");
			ast_print_helper(curr->scope.declarations_node, depth + 1);
			ast_print_helper(curr->scope.statements_node, depth + 1);
			print_indent(depth, 0, 1);
			break;
		case UNARY_EXPRESSION_NODE:
			print_indent(depth, 1, 0);
			fprintf(dumpFile, "UNARY %s %s ", get_type_str(curr->type_id), get_op_str(curr->unary_expr.op));
			ast_print_helper(curr->unary_expr.right, depth + 1);
			print_indent(depth, 0, 0);
			break;
		case BINARY_EXPRESSION_NODE:
			print_indent(depth, 1, 0);
			fprintf(dumpFile, "BINARY %s %s ", get_type_str(curr->type_id), get_op_str(curr->binary_expr.op));
			ast_print_helper(curr->binary_expr.left, depth + 1);
			ast_print_helper(curr->binary_expr.right, depth + 1);
			print_indent(depth, 0, 0);
			break;
		case INT_NODE:
			fprintf(dumpFile, "%d ", curr->int_val);
			break;
		case FLOAT_NODE:
			fprintf(dumpFile, "%f ", curr->float_val);
			break;
		case VAR_NODE:
			if (curr->var.index == -1) {
				fprintf(dumpFile, "%s ", curr->var.id_name);		
			} else {
				fprintf(dumpFile, "(INDEX %s %s %d) ", get_type_str(curr->type_id), curr->var.id_name, curr->var.index);
			}
			break;
		case FUNCTION_NODE:
			print_indent(depth, 1, 1);
			// dp3 -> 0, lit -> 1, rsq -> 2
			if (curr->function.function_id == 0) fprintf(dumpFile, "CALL %s ", "DP3");
			else if (curr->function.function_id == 1) fprintf(dumpFile, "CALL %s ", "LIT");
			else if (curr->function.function_id == 2) fprintf(dumpFile, "CALL %s ", "RSQ");
			ast_print_helper(curr->function.arguments_node, depth + 1);	
			print_indent(depth, 0, 0);
			break;
		case CONSTRUCTOR_NODE:
			print_indent(depth, 1, 1);
			fprintf(dumpFile, "CALL ");
			ast_print_helper(curr->constructor.type_node, depth + 1);
			ast_print_helper(curr->constructor.arguments_node, depth + 1);
			print_indent(depth, 0, 0);
			break;
		case IF_STATEMENT_NODE:
			print_indent(depth, 1, 1);
			fprintf(dumpFile, "IF ");
			ast_print_helper(curr->if_statement.condition_node, depth + 1);
			ast_print_helper(curr->if_statement.if_node, depth + 1);
			ast_print_helper(curr->if_statement.else_node, depth + 1);
			print_indent(depth, 0, 1);
			break;
		case ASSIGNMENT_NODE:
			print_indent(depth, 1, 1);
			fprintf(dumpFile, "ASSIGN %s ", get_type_str(curr->assignment.variable_node->type_id));
			ast_print_helper(curr->assignment.variable_node, depth + 1);
			ast_print_helper(curr->assignment.expression_node, depth + 1);
			print_indent(depth, 0, 0);
			break;
		case NESTED_SCOPE_NODE:
			ast_print_helper(curr->nested_scope_node, depth + 1);
			break;
		case STATEMENTS_NODE:
			print_indent(depth, 1, 1);
			fprintf(dumpFile, "STATEMENTS ");
			ast_print_helper(curr->statements.statements_node, depth + 1);			
			ast_print_helper(curr->statements.statement_node, depth + 1);
			print_indent(depth, 0, 1);
			break;
		case ARGUMENTS_NODE:
			ast_print_helper(curr->arguments.arguments_node, depth + 1);
			ast_print_helper(curr->arguments.expression_node, depth + 1);
			break;
		case TYPE_NODE:
			fprintf(dumpFile, "%s ", get_type_str(curr->type_id));
			break;
		case BOOL_NODE:
			if (curr->bool_val) fprintf(dumpFile, "true ");
			else fprintf(dumpFile, "false ");
			break;
		case DECLARATION_NODE:
			print_indent(depth, 1, 1);
			fprintf(dumpFile, "DECLARATION %s ", curr->declaration.id_name);
			ast_print_helper(curr->declaration.type_node, depth + 1);
			ast_print_helper(curr->declaration.expression_node, depth + 1);
			print_indent(depth, 0, 0);
			break;
		case DECLARATIONS_NODE:
			print_indent(depth, 1, 1);
			fprintf(dumpFile, "DECLARATIONS ");
			ast_print_helper(curr->declarations.declarations_node, depth + 1);
			ast_print_helper(curr->declarations.declaration_node, depth + 1);
			print_indent(depth, 0, 1);
			break;
		case EXPR_VAR_NODE:
			ast_print_helper(curr->expr_var.variable_node, depth + 1);	
			break;
		case NESTED_EXPRESSION_NODE:
			ast_print_helper(curr->nested_expression_node, depth + 1);	
			break;
		default:
			break;
	}
}

void ast_free_helper(node *curr) {
	if (curr == NULL) {
		return;	
	}
	
	switch(curr->kind) {
		case SCOPE_NODE:
			ast_free_helper(curr->scope.declarations_node);
			ast_free_helper(curr->scope.statements_node);
			break;
		case UNARY_EXPRESSION_NODE:
			ast_free_helper(curr->unary_expr.right);
			break;
		case BINARY_EXPRESSION_NODE:
			ast_free_helper(curr->binary_expr.left);
			ast_free_helper(curr->binary_expr.right);
			break;
		case INT_NODE:
			/* Do Nothing*/
			break;
		case FLOAT_NODE:
			/* Do Nothing*/
			break;
		case VAR_NODE:
			/* Do Nothing*/
			break;
		case FUNCTION_NODE:
			ast_free_helper(curr->function.arguments_node);	
			break;
		case CONSTRUCTOR_NODE:
			ast_free_helper(curr->constructor.type_node);
			ast_free_helper(curr->constructor.arguments_node);
			break;
		case IF_STATEMENT_NODE:
			ast_free_helper(curr->if_statement.condition_node);
			ast_free_helper(curr->if_statement.if_node);
			ast_free_helper(curr->if_statement.else_node);
			break;
		case ASSIGNMENT_NODE:
			ast_free_helper(curr->assignment.variable_node);
			ast_free_helper(curr->assignment.expression_node);
			break;
		case NESTED_SCOPE_NODE:
			ast_free_helper(curr->nested_scope_node);
			break;
		case STATEMENTS_NODE:
			ast_free_helper(curr->statements.statements_node);			
			ast_free_helper(curr->statements.statement_node);
			break;
		case ARGUMENTS_NODE:
			ast_free_helper(curr->arguments.arguments_node);
			ast_free_helper(curr->arguments.expression_node);
			break;
		case TYPE_NODE:
			/* Do Nothing*/
			break;
		case BOOL_NODE:
			/* Do Nothing*/
			break;
		case DECLARATION_NODE:
			ast_free_helper(curr->declaration.type_node);
			ast_free_helper(curr->declaration.expression_node);
			break;
		case DECLARATIONS_NODE:
			ast_free_helper(curr->declarations.declarations_node);
			ast_free_helper(curr->declarations.declaration_node);
			break;
		case EXPR_VAR_NODE:
			ast_free_helper(curr->expr_var.variable_node);
			break;
		case NESTED_EXPRESSION_NODE:
			ast_free_helper(curr->nested_expression_node);
			break;
		default:
			break;
	}
	free(curr);
}

void ast_free(node *ast) {
	ast_free_helper(ast);
}

void ast_print(node *ast) {
	ast_print_helper(ast, 0);
}
