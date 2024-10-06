#pragma once

#include "lexer.h"
#include "hashmap.h"
#include <type.h>

typedef struct {
	bool is_map;

	hashmap_t map;
	const char* val;
} val_t;

typedef hashmap_t parse_result_t;

parse_result_t parse_data(lex_result_t* lex);
const char* parse_get(parse_result_t *parse, const char* key);
