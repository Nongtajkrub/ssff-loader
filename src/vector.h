#pragma once

#include <type.h>

typedef struct {
	bool is_init;

	void** element;

	u32 element_size;
	u32 capacity;
	u32 size;
} vec_t;

void vec_init(vec_t* vec, u32 element_size);
void vec_deinit(vec_t* vec);

void vec_push(vec_t* vec, void* element);
void vec_pop(vec_t* vec);

void* vec_get(const vec_t* vec, u32 index);
