#include "parser.h"

#include "lexer.h"
#include <stdlib.h>
#include <stdarg.h>

#define NODE_TAIL_I_OFFSET 2
#define GET_NODE_TAIL_I(I) I + NODE_TAIL_I_OFFSET

static const u32 VAL_SIZE = sizeof(parse_val_t);
static parse_val_t* current_node_h = NULL;

static void handle_node_head(parse_result_t* parse, lex_result_t* lex, u32* i) {
	// get node head and node tail (node_head : node_tail)
	token_t* node_h = (token_t*)vec_get(lex, *i);
	token_t* node_t = (token_t*)vec_get(lex, GET_NODE_TAIL_I(*i));
	
	// creating item to add to map 
	const char* key = node_h->data;

	parse_val_t val = {
		.is_map = (node_t->type == NODE_HEAD) ? TRUE : FALSE,
		.data = (val.is_map) ? malloc(sizeof(hashmap_t)) : (void*)node_t->data
	};
	if (val.is_map) {
		map_init((hashmap_t*)val.data, KEY_IS_STR, VAL_SIZE, DEF_MAP_SIZE);
	}

	// add item to the correct map
	map_add(
		(current_node_h == NULL) ? parse : (hashmap_t*)current_node_h->data,
		(void*)key,
		(void*)&val
		);

	// update current_node_h if needed
	if (val.is_map) {
		current_node_h = (parse_val_t*)map_get(
			(current_node_h == NULL) ? parse : (hashmap_t*)current_node_h->data,
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

	return parse;
}

// use int for key_count to prevent argument promotion
void* parser_get(parse_result_t* parse, int key_count, ...) {
	if (key_count <= 0) {
		return NULL;
	}

	va_list keys;
	va_start(keys, key_count);
	hashmap_t* node_h = parse;

	printf("getting\n");
	for (u16 i = 0; i < key_count; i++) {
		char* key = va_arg(keys, char*);
		parse_val_t* val = (parse_val_t*)map_get(node_h, key);

		if (i == (key_count - 1)) {
			va_end(keys);
			return (void*)val->data;
		}
		if (!val->is_map) {
			va_end(keys);
			return NULL;
		}
		node_h = (hashmap_t*)val->data;
	}

	va_end(keys);
	return NULL;
}
