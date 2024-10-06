#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEF_HASHING_FACTOR 31

static const u32 HASHMAP_ITEM_SIZE = sizeof(hashmap_item_t);

// copy from the internet
static u32 hash(hashmap_t* map, char* key) {
    u32 bucket_i = 0;
	u32 factor = DEF_HASHING_FACTOR;
	u32 key_size = (map->key_is_str) ? strlen(key) : map->key_size;

    for (u32 i = 0; i < key_size; i++) {
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
	map->key_is_str = (key_size == KEY_IS_STR) ? TRUE : FALSE;

	map->key_size = key_size;
	map->val_size = val_size;
	map->size = map_size;

	map->items = calloc(map_size, HASHMAP_ITEM_SIZE);
}

void map_key_is_str(hashmap_t* map) {
	map->key_is_str = TRUE;
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
	u32 key_size = (map->key_is_str) ? strlen((char*)key) : map->key_size;

	// allocate memory for new item
	hashmap_item_t* new_item = malloc(HASHMAP_ITEM_SIZE);
	ASSERT(new_item != NULL, DEF_ALLOC_ERRMSG);
	
	new_item->key = malloc(key_size);
	ASSERT(new_item->key != NULL, DEF_ALLOC_ERRMSG);
	new_item->val = malloc(map->val_size);
	ASSERT(new_item->val != NULL, DEF_ALLOC_ERRMSG);
	new_item->next = NULL;

	// copy key and value data into new item
	memcpy(new_item->key, key, key_size);
	memcpy(new_item->val, val, map->val_size);

	// enusure null terminated
	if (map->key_is_str) {
		new_item->key[key_size] = '\0';
	}

	// add item to hashmap
	if (map->items[bucket_i] != NULL) {
		new_item->next = map->items[bucket_i];
	}
	map->items[bucket_i] = new_item;
}

void* map_get(hashmap_t* map, void* key) {
	u32 bucket_i = hash(map, (char*)key);
	hashmap_item_t *bucket_h = map->items[bucket_i];
	
	if (bucket_h == NULL) {
		printf("Bucket head not found for: %s\n", (char*)key);
		return NULL;
	}

	while (bucket_h != NULL) {
		// IFERR: Casting key to char*
		if (strcmp(bucket_h->key, (char*)key) == 0) {
			return bucket_h->val;
		}
		bucket_h = bucket_h->next;
	}

	// no bucket found
	return NULL;
}

void* map_get_key(hashmap_t* map, void* key) {
	u32 bucket_i = hash(map, (char*)key);
	hashmap_item_t *bucket_h = map->items[bucket_i];
	
	if (bucket_h == NULL) {
		return NULL;
	}

	while (bucket_h != NULL) {
		if (strcmp(bucket_h->key, key) == 0) {
			return bucket_h->key;
		}
		bucket_h = bucket_h->next;
	}

	// should not reach this but if does assume failure
	return NULL;
}
