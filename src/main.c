#define DEF_DATA_FILE_NAME "data.ssff"

#include "file.h"
#include "parser.h"

int main() {
	file_t file;
	lex_result_t lex;
	parse_result_t parse;

	// get raw file data
	file_init(&file, DEF_DATA_FILE_NAME);

	// lex data
	lex = lex_data(file.content, file.size);

	/*
	for (u32 i = 0; i < lex.size; i++) {
		printf("%s\n", lex_get(&lex, i).data);
	}
	*/

	// parse data
	parse = parse_data(&lex);

	// get data
	printf(
			"data: %s\n",
			(char*)parser_get(&parse, 3, "pakthan", "bw_punishment", "soft")
			);

	file_deinit(&file);
	lex_destroy(&lex);
	printf("done\n");
	return 0;
}
