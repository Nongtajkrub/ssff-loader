#include "parser.h"

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

#define NODE_TAIL_I_OFFSET 2
#define GET_NODE_TAIL_I(I) I + NODE_TAIL_I_OFFSET

static const u32 VAL_SIZE = sizeof(val_t);
static val_t* current_node_h = NULL;

static void handle_node_head(parse_result_t* parse, lex_result_t* lex, u32* i) {
	// get node head and node tail (node_head : node_tail)
	token_t* node_h = (token_t*)vec_get(lex, *i);
	token_t* node_t = (token_t*)vec_get(lex, GET_NODE_TAIL_I(*i));
	
	// creating item to add to map 
	const char* key = node_h->data;

	val_t val = {
		.is_map = (node_t->type == NODE_HEAD) ? TRUE : FALSE,
		.val = (val.is_map) ? NULL : node_t->data
	};
	if (val.is_map) {
		map_init(&val.map, KEY_IS_STR, VAL_SIZE, DEF_MAP_SIZE);
	}

	// add item to the correct map
	map_add(
		(current_node_h == NULL) ? parse : &current_node_h->map,
		(void*)key, &val
		);

	// update current_node_h if needed
	if (val.is_map) {
		current_node_h = (val_t*)map_get(
			(current_node_h == NULL) ? parse : &current_node_h->map,
			(void*)key
			);
	}
}

void handle_node_ender() {
	current_node_h = NULL;
}

parse_result_t parse_data(lex_result_t* lex) {
	parse_result_t parse;
	token_t* token;

	map_init(&parse, KEY_IS_STR, VAL_SIZE, DEF_MAP_SIZE);

	for (u32 i = 0; i < lex->size; i++) {
		token = (token_t*)vec_get(lex, i);

		switch (token->type) {
		case NODE_HEAD:
			handle_node_head(&parse, lex, &i);
			break;
		case NODE_ENDER:
			handle_node_ender();
			break;
		default:
			break;
		}
	}

	lex_destroy(lex);
	return parse;
}
