#define DEF_DATA_FILE_NAME "data.txt"

#include "parser.h"

int main() {
	file_t file;
	parse_result_t parse;

	file_init(&file, DEF_DATA_FILE_NAME);

	parse = parse_data(&file);

	/*
	val_t* soft = (val_t*)map_get(&data->map, &type);

	printf("%s\n", soft->val);
	*/

	printf("done\n");
	file_deinit(&file);
	return 0;
}
