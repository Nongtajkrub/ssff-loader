#define DEF_DATA_FILE_NAME "data.txt"

#include "parser.h"

int main() {
	file_t file;
	lex_result_t lex;
	parse_result_t parse;

	// get raw file data
	file_init(&file, DEF_DATA_FILE_NAME);

	// lex data
	lex = lex_data(file.content, file.size);

	// parse data
	parse = parse_data(&lex);

	file_deinit(&file);
	lex_destroy(&lex);
	printf("done\n");
	return 0;
}
