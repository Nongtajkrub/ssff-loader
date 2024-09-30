#define DEF_DATA_FILE_NAME "data.txt"

#include "vector.h"
#include "file.h"
#include "lexer.h"

int main() {
	file_t file;
	vec_t lex_result;
	token_t token;

	file_init(&file, DEF_DATA_FILE_NAME);
	
	lex_result = lex_data(file.content, file.size);

	for (u32 i = 0; i < lex_result.size; i++) {
		vec_get(&lex_result, i, (char*)&token);
		printf("%s = %d\n", token.data, token.type);
	}

	file_deinit(&file);
	lex_destroy(&lex_result);
	return 0;
}
