#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdlib.h>

#define CHDS_VECTOR_GROWTH_FACTOR 1.5f

typedef struct
{
    size_t count;
    size_t capacity;

} CHDS_VectorHeader;

// Define a vector type.
#define Vector(T) T*

// TODO: Private.
// Return the vector header.
#define CHDS_Vector_header(v) ((CHDS_VectorHeader*)(v) - 1)

// Return the number of elements in the vector.
#define Vector_size(v) CHDS_Vector_header((v))->count

// Add a value to the vector.
#define Vector_push_back(v, value) do \
{ \
    CHDS_Vector_grow_if_needed(&(v), sizeof(*v)); \
    (v)[CHDS_Vector_header((v))->count++] = (value); \
    \
 \
} while (0)

inline void CHDS_Vector_grow_if_needed(void** v, size_t element_size)
{
    CHDS_VectorHeader* h = 0;
    size_t count = 0;
    size_t capacity = 1;

    if (*v)
    {
        h = CHDS_Vector_header(*v);
        if (h->count < h->capacity) return;

        // Determine how much to grow the vector by.
        size_t extra = (h->capacity * CHDS_VECTOR_GROWTH_FACTOR);
        if (extra == 0) extra = 1;

        capacity = h->capacity + extra;
        count = h->count;
    }
    
    size_t size = sizeof(CHDS_VectorHeader) + capacity * element_size;

    // TODO: Rename from temp.
    CHDS_VectorHeader* temp = realloc(h, size);
    if (!temp)
    {
        // TODO: How can we possibly handle failure?
        return;
    }

    CHDS_VectorHeader* new_header = temp;
    new_header->capacity = capacity;
    new_header->count = count;

    *v = new_header + 1;
}

inline void Vector_destroy(void* v)
{
    // TODO: Free elements individually? Would require dtor func.
    if (v) free(CHDS_Vector_header(v));
}


#endif