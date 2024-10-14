#pragma once

#include "vector.h"
#include <type.h>

typedef vec_t lex_result_t;

typedef enum {
	UNKNOWN,
	NODE_HEAD,
	NODE_STARTER,
	NODE_TAIL,
	NODE_NEXT,
	NODE_ENDER
} token_type_t;

typedef struct {
	char* data;

	token_type_t type;
} token_t;

lex_result_t lex_data(const char* data, u32 size);
void lex_destroy(lex_result_t* lex_result);

token_t lex_get(lex_result_t* lex_result, u32 index);
