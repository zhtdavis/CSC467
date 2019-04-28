#ifndef SYMBOL_H_
#define SYMBOL_H_ 1


struct symbol_table_entry_;
typedef struct symbol_table_entry_ symbol_table_entry;

struct symbol_table_entry_ {
	int is_const;
	int type_id;
	int depth;
	char *id_name;
	symbol_table_entry *prev;
};

void print_symbol_table();

symbol_table_entry *search_symbol_table(char *id_name);

void add_new_entry(int is_const, int type_id, int depth, char *id_name);

bool check_pre_existing_symbol(char *id_name);

void add_pre_defined_variable_entry();

#endif
