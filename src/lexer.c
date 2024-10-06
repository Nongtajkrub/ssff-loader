#include "lexer.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>

// whitespaces
#define SPACE ' '
#define NEW_LINE_N '\n'
#define NEW_LINE_R '\r'
#define TAP '\t'

// operator
#define ASSIGNMENT_OPERATOR ':'
#define COMMA_SEPARATOR ','
#define STATEMENT_TERMINATOR ';'

static void substr(char* buf, u32 size, const char* src, u32 i1, u32 i2) {
	strncpy_s(buf, size, src + i1, i2 - 1);
}

static void add_token(lex_result_t* buf, const char* data, token_type_t type) {
	const u32 data_size = strlen(data) + 1;	

	token_t token = {
		.data = malloc(data_size),
		.type = type 
	};
	strcpy_s(token.data, data_size, data);

	vec_push(buf, (void*)&token);
}

static void seperate_token(
	const char* data,
	u32* last_seperation,
	u32 i,
	token_type_t type,
	lex_result_t* buf
	) {
	u32 seperation_size = (i - *last_seperation) + 1;
	char* seperated_token = malloc(seperation_size);
	ASSERT(seperated_token != NULL, DEF_ALLOC_ERRMSG);

	// extract the substring
	substr(
		seperated_token,  // buf
		seperation_size,  // size
		data,             // src
		*last_seperation, // from
		seperation_size   // to
		);
	// update last_seperation for the next token
	*last_seperation = i; 

	// add the token to the buffer
	add_token(buf, seperated_token, type);
	
	free(seperated_token);
}

lex_result_t lex_data(const char* data, u32 size) {
	lex_result_t lex_result;
	u32 last_seperation = 0;
	// buffer to convert a character to a string
	char char_to_str[2] = {'\0', '\0'};

	vec_init(&lex_result, sizeof(token_t));

	for (u32 i = 0; i < size; i++) {
		switch (data[i]) {
		case SPACE:
		case TAP:
		case NEW_LINE_N:
		case NEW_LINE_R:
			// ignore the SPACE, NEW_LINE_N, NEW_LINE_R and TAP character
			// on next seperation
			last_seperation++;
			break;
		case ASSIGNMENT_OPERATOR:
			seperate_token(data, &last_seperation, i, NODE_HEAD, &lex_result);

			char_to_str[0] = ASSIGNMENT_OPERATOR;
			add_token(&lex_result, char_to_str, NODE_STARTER);

			// ignore the ASSIGNMENT_OPERATOR character on next seperation
			last_seperation++;
			break;
		case COMMA_SEPARATOR:
			seperate_token(data, &last_seperation, i, NODE_TAIL, &lex_result);

			char_to_str[0] = COMMA_SEPARATOR;
			add_token(&lex_result, char_to_str, NODE_NEXT);

			// ignore the COMMA_SEPARATOR character on next seperation
			last_seperation++;
			break;
		case STATEMENT_TERMINATOR:
			seperate_token(data, &last_seperation, i, NODE_TAIL, &lex_result);

			char_to_str[0] = STATEMENT_TERMINATOR;
			add_token(&lex_result, char_to_str, NODE_ENDER);

			// ignore the STATEMENT_TERMINATOR character on next seperation
			last_seperation++;
			break;
		default:
			break;
		}
	}

	return lex_result;
}

// TODO: Fix lex_destroy crashing
void lex_destroy(lex_result_t *lex_result) {
	if (lex_result == NULL) {
		return;
	}

	token_t* token_buf;

	// free all malloc memory 
	for (u32 i = 0; i < lex_result->size; i++) {
		token_buf = (token_t*)vec_get(lex_result, i);
		if (token_buf->data != NULL) {
			free(token_buf->data);
		}	
	}

	vec_deinit(lex_result);
}

token_t lex_get(lex_result_t* lex_result, u32 index) {
	return *(token_t*)vec_get(lex_result, index);
}
