#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_HASHING_FACTOR 31

// copy from the internet
static u32 hash(hashmap_t* map, char* key) {
    u32 bucket_i = 0;
	u32 factor = DEF_HASHING_FACTOR;

    for (u32 i = 0; i < map->key_size; i++) {
		// bucket_i = bucket_i + (ascii value of char * (primeNumber ^ x))... 
		// where x = 1, 2, 3....n
        bucket_i = ((bucket_i % map->size) 
				   	+ (((u32)key[i]) * factor) % map->size) 
						% map->size;
	 
		// factor = factor * prime number....(prime number) ^ x
        factor = ((factor % __INT16_MAX__) 
				  	* (DEF_HASHING_FACTOR % __INT16_MAX__)) 
						% __INT16_MAX__;
    }

    return bucket_i;
}

void map_init(hashmap_t* map, u32 key_size, u32 val_size, u32 map_size) {
	map->key_size = key_size;
	map->val_size = val_size;
	map->size = map_size;

	map->items = calloc(map_size, sizeof(hashmap_item_t));
}

void map_deinit(hashmap_t* map) {
	for (u32 i = 0; i < map->size; i++) {
		if (map->items[i] != NULL) {
			free(map->items[i]);
		}
	}
	free(map->items);
}

void map_add(hashmap_t* map, void* key, void* val) {
	u32 bucket_i = hash(map, (char*)key);
	hashmap_item_t* new_item = malloc(sizeof(hashmap_item_t));

	printf("bucket index add: %d\n", bucket_i);
	
	new_item->key = malloc(map->key_size);
	new_item->val = malloc(map->val_size);
	new_item->next = NULL;

	memcpy(new_item->key, key, map->key_size);
	memcpy(new_item->val, val, map->val_size);

	if (map->items[bucket_i] != NULL) {
		new_item->next = map->items[bucket_i];
	}
	map->items[bucket_i] = new_item;
}

void* map_get(hashmap_t* map, void* key) {
	u32 bucket_i = hash(map, (char*)key);
	hashmap_item_t *bucket_h = map->items[bucket_i];
	
	printf("bucket index get: %d\n", bucket_i);

	if (bucket_h == NULL) {
		return NULL;
	}

	while (bucket_h != NULL) {
		if (strcmp(bucket_h->key, key) == 0) {
			return bucket_h->val;
		}
		bucket_h = bucket_h->next;
	}

	// should not reach this but if does assume failure
	return NULL;
}
