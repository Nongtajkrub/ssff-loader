#include "parser.h"
#include "lexer.h"

#define NODE_VAL_OFFSET 2
#define GET_NODE_VAL_I(I) I + NODE_VAL_OFFSET

typedef struct {
	const char* data;
} hashmap_keyval_t;

static const u32 KEYVAL_SIZE = sizeof(hashmap_keyval_t);

static void handle_node_name(
	parse_result_t* parse,
	lex_result_t* lex,
	const token_t* token,
	u32* i
	) {
	// create key and value for hashmap
	hashmap_keyval_t key = {
		.data = token->data
	};
	hashmap_keyval_t val = {
		.data = lex_get(lex, GET_NODE_VAL_I(*i)).data
	};
	
	printf("key %s\n", key.data);

	// add key and value to hashmap
	map_add(parse, &key, &val);
	// skip this node to the next node
	//*i += 2;
}

parse_result_t parse_data(const file_t* data) {
	parse_result_t parse;
	lex_result_t lex;
	token_t token;

	lex = lex_data(data->content, data->size);
	map_init(&parse, KEYVAL_SIZE, KEYVAL_SIZE, DEF_MAP_SIZE);
	
	for (u32 i = 0; i < lex.size; i++) {
		token = lex_get(&lex, i);

		switch (token.type) {
		case NODE_NAME:
			handle_node_name(&parse, &lex, &token, &i);
			break;
		default:
			break;
		}
	}

	printf("%s\n", parse_get(&parse, "Taj"));

	lex_destroy(&lex);
	return parse;
}

const char* parse_get(parse_result_t* parse, const char* key) {
	hashmap_keyval_t _key = {
		.data = key
	};

	return ((hashmap_keyval_t*)map_get(parse, &_key))->data;
}
