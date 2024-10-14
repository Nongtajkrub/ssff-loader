#pragma once

#include "lexer.h"
#include "hashmap.h"
#include <type.h>

typedef enum {
	INT,
	STR,
	FLOAT,
	BOOL
} datatype_t;

typedef struct {
	bool is_map;

	// could be hashmap_t or just a void*
	void* data;
} parse_val_t;

typedef hashmap_t parse_result_t;

parse_result_t parse_data(lex_result_t* lex);
void* parser_get(parse_result_t* parse, int key_count, ...);
