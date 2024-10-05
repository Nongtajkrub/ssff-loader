#include "parser.h"

#include "lexer.h"
#include <stdio.h>

#define NODE_TAIL_I_OFFSET 2
#define GET_NODE_TAIL_I(I) I + NODE_TAIL_I_OFFSET

static const u32 VAL_SIZE = sizeof(val_t);
static val_t* current_node_h = NULL;

static void handle_node_head(parse_result_t* parse, lex_result_t* lex, u32* i) {
	token_t* node_h = (token_t*)vec_get(lex, *i);
	token_t* node_t = (token_t*)vec_get(lex, GET_NODE_TAIL_I(*i));

	printf(
		"node_head {\n\tkey: [%s, %d],\n\tval: [%s, %d]\n}\n",
		node_h->data, node_h->type, node_t->data, node_t->type
		);

	const char* key = node_h->data;

	val_t val = {
		.is_map = (node_t->type == NODE_HEAD) ? TRUE : FALSE,
		.val = (val.is_map) ? NULL : node_t->data
	};
	if (val.is_map) {
		printf("node_head: is_map\n");
		map_init(&val.map, KEY_IS_STR, VAL_SIZE, DEF_MAP_SIZE);
	}

	if (current_node_h != NULL) {
		printf("node_head: is_nest\n");
		map_add(&current_node_h->map, (void*)key, &val);
	} else {
		printf("node_head: is_not_nest\n");
		map_add(parse, (void*)key, &val);
	}

	if (val.is_map) {
		printf("node_head: change_current_node_h\n");
		current_node_h = (val_t*)map_get(parse, (void*)key);
	}

	printf("Handled node head\n\n");
}

void handle_node_ender() {
	current_node_h = NULL;
}

parse_result_t parse_data(const file_t* data) {
	parse_result_t parse;
	lex_result_t lex;
	token_t* token;

	map_init(&parse, KEY_IS_STR, VAL_SIZE, DEF_MAP_SIZE);
	lex = lex_data(data->content, data->size);

	for (u32 i = 0; i < lex.size; i++) {
		token = (token_t*)vec_get(&lex, i);

		switch (token->type) {
		case NODE_HEAD:
			handle_node_head(&parse, &lex, &i);
			break;
		case NODE_ENDER:
			handle_node_ender();
			break;
		default:
			break;
		}
	}

	printf("\n----------------------------------------------\n");
	
	val_t* _data = (val_t*)map_get(&parse, "Pakthan");
	printf("is map -> %d\n", _data->is_map);

	lex_destroy(&lex);
	return parse;
}
