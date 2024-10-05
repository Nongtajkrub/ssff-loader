#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_NOT_ALLOC_ERRMSG \
	"Vector was not allocated before being use"
#define OUT_OF_RANGE_ERRMSG \
	"Index exceed vec size"

#define DEF_CAPACITY 4 

void vec_init(vec_t* vec, u32 element_size) {
	vec->element = calloc(DEF_CAPACITY, sizeof(void*));
	ASSERT(vec->element != NULL, DEF_ALLOC_ERRMSG);

	vec->element_size = element_size;
	vec->capacity = DEF_CAPACITY;
	vec->size = 0;
	vec->is_init = TRUE;
}

void vec_deinit(vec_t* vec) {
	if (!vec->is_init) {
		return;
	}

	vec->is_init = FALSE;
	for (u32 i = 0; i < vec->size; i++) {
		free(vec->element[i]);
	}
	free(vec->element);
}

static void handle_vec_full(vec_t* vec) {
	if (vec->size > 0 && vec->size % vec->capacity == 0) {
		vec->capacity = (vec->size / DEF_CAPACITY + 1) * DEF_CAPACITY;
		vec->element = realloc(vec->element, vec->capacity * sizeof(void*));
		ASSERT(vec->element != NULL, DEF_ALLOC_ERRMSG);
	}
}

void vec_push(vec_t* vec, void* element) {
	ASSERT(vec != NULL && vec->element != NULL, VECTOR_NOT_ALLOC_ERRMSG);

	handle_vec_full(vec);

	vec->element[vec->size] = malloc(vec->element_size);
	memcpy(vec->element[vec->size], element, vec->element_size);
	vec->size++;
}

void vec_pop(vec_t* vec) {
	if (vec->size > 0) {
		vec->element[vec->size - 1] = 0;
		vec->size--;
	}
}

void* vec_get(const vec_t* vec, u32 index) {
	ASSERT(vec != NULL && vec->element != NULL, VECTOR_NOT_ALLOC_ERRMSG);
	ASSERT(index < vec->size, OUT_OF_RANGE_ERRMSG);

	//memcpy(buf, vec->element[index], vec->element_size);
	return vec->element[index];
}
