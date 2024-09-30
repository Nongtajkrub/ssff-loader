#pragma once

#include <type.h>

typedef struct {
	const char* path;
	u32 size;

	char* content;
} file_t;

void file_init(file_t *file, const char* path);
void file_deinit(file_t *file);
