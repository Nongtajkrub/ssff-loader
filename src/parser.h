#pragma once

#include "file.h"
#include "hashmap.h"
#include <type.h>

typedef hashmap_t parse_result_t;

parse_result_t parse_data(const file_t* data);
const char* parse_get(parse_result_t *parse, const char* key);
