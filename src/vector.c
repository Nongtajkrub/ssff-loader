#include "vector.h"

#include <stdlib.h>
#include <string.h>

#define VECTOR_NOT_ALLOC_ERRMSG \
	"Vector was not allocated before being use"
#define OUT_OF_RANGE_ERRMSG \
	"Index exceed vec size"

#define DEF_CAPACITY 4 

void vec_init(vec_t* vec, u32 element_size) {
	ASSERT(vec != NULL, DEF_ALLOC_ERRMSG);

	vec->element = calloc(DEF_CAPACITY, sizeof(char*));
	ASSERT(vec->element != NULL, DEF_ALLOC_ERRMSG);
	vec->element_size = element_size;
	vec->capacity = DEF_CAPACITY;
	vec->size = 0;
	vec->init = TRUE;
}

void vec_deinit(vec_t* vec) {
	if (!vec->init) {
		return;
	}

	vec->init = FALSE;
	for (u32 i = 0; i < vec->size; i++) {
		free(vec->element[i]);
	}
	free(vec->element);
}

void vec_push(vec_t* vec, char* element) {
	ASSERT(vec != NULL && vec->element != NULL, VECTOR_NOT_ALLOC_ERRMSG);

	// vec is full
	if (vec->size > 0 && vec->size % vec->capacity == 0) {
		vec->capacity = (vec->size / DEF_CAPACITY + 1) * DEF_CAPACITY;
		vec->element = realloc(vec->element, vec->capacity * sizeof(char*));
		ASSERT(vec->element != NULL, DEF_ALLOC_ERRMSG);
	}

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

void vec_get(const vec_t* vec, u32 index, char* buf) {
	ASSERT(vec != NULL && vec->element != NULL, VECTOR_NOT_ALLOC_ERRMSG);
	ASSERT(index < vec->size, OUT_OF_RANGE_ERRMSG);

	memcpy(buf, vec->element[index], vec->element_size);
}
