#ifndef AST_H_
#define AST_H_ 1

#include <stdarg.h>

// Dummy node just so everything compiles, create your own node/nodes
//
// The code provided below is an example ONLY. You can use/modify it,
// but do not assume that it is correct or complete.
//
// There are many ways of making AST nodes. The approach below is an example
// of a descriminated union.
//

// Forward declarations
struct node_;
typedef struct node_ node;
extern node *ast;

typedef enum {
  UNKNOWN               = 0,

  SCOPE_NODE            = (1 << 0),
  
  //EXPRESSION_NODE       = (1 << 2),
  UNARY_EXPRESSION_NODE  = (1 << 2) | (1 << 3),
  BINARY_EXPRESSION_NODE= (1 << 2) | (1 << 4),
  INT_NODE              = (1 << 2) | (1 << 5), 
  FLOAT_NODE            = (1 << 2) | (1 << 6),
  //IDENT_NODE            = (1 << 2) | (1 << 7),
  VAR_NODE              = (1 << 2) | (1 << 8),
  FUNCTION_NODE         = (1 << 2) | (1 << 9),
  CONSTRUCTOR_NODE      = (1 << 2) | (1 << 10),

  //STATEMENT_NODE        = (1 << 1),
  IF_STATEMENT_NODE     = (1 << 1) | (1 << 11),
  //WHILE_STATEMENT_NODE  = (1 << 1) | (1 << 12),
  ASSIGNMENT_NODE       = (1 << 1) | (1 << 13),
  NESTED_SCOPE_NODE     = (1 << 1) | (1 << 14),
  // new
  STATEMENTS_NODE	    = (1 << 1) | (1 << 15),
  ARGUMENTS_NODE		= (1 << 1) | (1 << 16),
  TYPE_NODE				= (1 << 1) | (1 << 17),
  BOOL_NODE				= (1 << 1) | (1 << 18),

  DECLARATION_NODE      = (1 << 19),
  // new
  DECLARATIONS_NODE		= (1 << 20),
  EXPR_VAR_NODE			= (1 << 21),
  NESTED_EXPRESSION_NODE= (1 << 22)
} node_kind;

struct node_ {

  // an example of tagging each node with a type
  node_kind kind;
  int type_id;
  int line_num;

  // phase 4
  char *temp_var_name;

  union {

	int int_val;
	float float_val;
	bool bool_val;
	node *nested_scope_node;
	node *nested_expression_node;
    
	struct {
      node *declarations_node;
	  node *statements_node;
    } scope;
  
    struct {
      int op;
      node *right;
    } unary_expr;

    struct {
      int op;
      node *left;
      node *right;
    } binary_expr;

	struct {
	  node *condition_node;
	  node *if_node;
	  node *else_node;
	} if_statement;

	struct {
	  node *variable_node;
	  node *expression_node;
	} assignment;
	
	struct {
	  int is_const;
	  node *type_node;
	  char *id_name;
	  node *expression_node;
	} declaration;
	
	struct {
	  node *arguments_node;
	  node *expression_node;
	} arguments;

	struct {
	  char *id_name;
	  int index;
	} var;

	struct {
	  int function_id;
	  node *arguments_node;	
	} function;

	struct {
	  node *type_node;
	  node *arguments_node;
	} constructor;

	struct {
	  node *variable_node;
	} expr_var;

	struct {
	  node *statements_node;
	  node *statement_node;
	} statements;

	struct {
	  node *declarations_node;
	  node *declaration_node;
	} declarations;
  };
};

node *ast_allocate(node_kind type, ...);
void ast_free(node *ast);
void ast_print(node * ast);

#endif /* AST_H_ */
