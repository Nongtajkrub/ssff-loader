#pragma once

#include "vector.h"
#include <type.h>

#define DEF_MAP_SIZE 32
#define KEY_IS_STR 0

typedef struct map_item {
	char* key;
	char* val;

	struct map_item* next;
} hashmap_item_t;

typedef struct {
	bool key_is_str;

	u32 key_size;
	u32 val_size;
	u32 size;

	hashmap_item_t** items;
} hashmap_t;

void map_init(hashmap_t* map, u32 key_size, u32 val_size, u32 map_size);
void map_deinit(hashmap_t* map);

void map_add(hashmap_t* map, void* key, void* val);
void* map_get(hashmap_t* map, void* key);
void* map_get_key(hashmap_t* map, void* key);
