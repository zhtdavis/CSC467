#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "symbol.h"
#include "common.h"

extern symbol_table_entry *curr_table_entry;

extern int scope_depth;

void print_symbol_table() {
	symbol_table_entry *curr = curr_table_entry;
	while (curr != NULL) {
		fprintf(dumpFile, "%d %d %s\n", curr->is_const, curr->type_id, curr->id_name);
		curr = curr->prev;	
	}
}

symbol_table_entry *search_symbol_table(char *id_name) {
	symbol_table_entry *curr = curr_table_entry;
	while (curr != NULL) {
		if (strcmp(curr->id_name, id_name) == 0) {
			return curr;		
		}
		curr = curr->prev;
	}
	return NULL;
}

void add_new_entry(int is_const, int type_id, int depth, char *id_name) {
	symbol_table_entry *new_entry = (symbol_table_entry *) malloc(sizeof(symbol_table_entry));
	new_entry->is_const = is_const;
	new_entry->type_id = type_id;	
	new_entry->depth = depth;	
	new_entry->id_name = id_name;
	new_entry->prev = curr_table_entry;
	curr_table_entry = new_entry;
}

bool check_pre_existing_symbol(char *id_name) {
	symbol_table_entry *curr = curr_table_entry;
	while (curr != NULL) {
		if (strcmp(curr->id_name, id_name) == 0 && curr->depth == scope_depth) {
			return true;		
		}
		curr = curr->prev;
	}
	return false;
}

void add_pre_defined_variable_entry() {
	/*
	result: gl_FragColor gl_FragDepth gl_FragCoord
	attribute: gl_TexCoord gl_Color gl_Secondary gl_FogFragCoord
	uniform: gl_Light_Half gl_Light_Ambient gl_Material_Shininess env1 env2 env3
	*/

	add_new_entry(0, 11, scope_depth, strdup("gl_FragColor"));
	add_new_entry(0, 4, scope_depth, strdup("gl_FragDepth"));
	add_new_entry(0, 11, scope_depth, strdup("gl_FragCoord"));

	add_new_entry(1, 11, scope_depth, strdup("gl_TexCoord"));
	add_new_entry(1, 11, scope_depth, strdup("gl_Color"));
	add_new_entry(1, 11, scope_depth, strdup("gl_Secondary"));
	add_new_entry(1, 11, scope_depth, strdup("gl_FogFragCoord"));

	add_new_entry(1, 11, scope_depth, strdup("gl_Light_Half"));
	add_new_entry(1, 11, scope_depth, strdup("gl_Light_Ambient"));
	add_new_entry(1, 11, scope_depth, strdup("gl_Material_Shininess"));
	add_new_entry(1, 11, scope_depth, strdup("env1"));
	add_new_entry(1, 11, scope_depth, strdup("env2"));
	add_new_entry(1, 11, scope_depth, strdup("env3"));
}
