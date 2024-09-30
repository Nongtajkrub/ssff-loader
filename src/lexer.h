#pragma once

#include "vector.h"
#include "file.h"
#include <type.h>

typedef enum {
	UNKNOWN,
	NODE_NAME,
	NODE_STARTER,
	NODE_VALUE,
	NODE_NEXT,
	NODE_ENDER
} token_type_t;

typedef struct {
	char* data;

	token_type_t type;
} token_t;

vec_t lex_data(const char* data, u32 size);
void lex_destroy(vec_t* lex_result);
