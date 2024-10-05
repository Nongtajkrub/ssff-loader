#define DEF_DATA_FILE_NAME "data.txt"

#include "parser.h"

int main() {
	file_t file;
	parse_result_t parse;

	file_init(&file, DEF_DATA_FILE_NAME);

	parse = parse_data(&file);

	file_deinit(&file);
	return 0;
}
