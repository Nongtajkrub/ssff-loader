#define _CRT_SECURE_NO_WARNINGS

#include "file.h"
#include <stdio.h>
#include <stdlib.h>

#define FAIL_TO_OPEN_FILE_ERR_MSG \
	"Fail to open data file"
#define FAIL_TO_READ_FILE_ERR_MSG \
	"Fail to read dat file"

static void load_file(file_t *file); 

void file_init(file_t *file, const char* path) {
	file->size = 0;
	file->path = path;
	load_file(file);
}

void file_deinit(file_t *file) {
	free(file->content);
}

// use to load text data from file
static void load_file(file_t *file) {
	size_t f_size;
	FILE *fd = fopen(file->path, "rb");

	ASSERT(fd != NULL, FAIL_TO_OPEN_FILE_ERR_MSG);

	// get file size
	fseek(fd, 0, SEEK_END);
	f_size = ftell(fd);
	file->size = f_size;
	rewind(fd);

	// allocate memory for storing file data with the size of the file size
	file->content = malloc(f_size + 1);
	ASSERT(file->content != NULL, FAIL_TO_READ_FILE_ERR_MSG);

	// read the data from file
	if (fread(file->content, 1, f_size, fd) != f_size) {
		ASSERT(1, FAIL_TO_READ_FILE_ERR_MSG);
	}
	file->content[f_size] = '\0';
	
	fclose(fd);
}
