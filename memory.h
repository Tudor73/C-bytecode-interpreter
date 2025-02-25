#ifndef memory_h
#define memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) \
	((capacity) < 8 ? 8 : (capacity) * 2)

#endif

void *reallocate(void *p, size_t old_size, size_t new_size);