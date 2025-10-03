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

// TODO: Make private.
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
} while (0)

// Increases the capacity of the vector to hold the given number of elements.
#define Vector_reserve(v, capacity) CHDS_Vector_reserve(&(v), capacity, sizeof(*v))

// Releases the underlying vector array.
inline void Vector_destroy(void* v)
{
    // TODO: Free elements individually? Would require dtor func.
    if (v) free(CHDS_Vector_header(v));
}

// TODO: Private methods. Could be hidden by actually turning into lib rather than header only.
inline CHDS_VectorHeader* CHDS_Vector_set_capacity(CHDS_VectorHeader* h, size_t capacity, size_t element_size)
{
    // Copy old header data.
    size_t count = 0;
    if (h)
    {
        count = h->count;
    }

    size_t size = sizeof(CHDS_VectorHeader) + capacity * element_size;

    CHDS_VectorHeader* vector = realloc(h, size);
    if (!vector)
    {
        // TODO: How can we possibly handle failure?
        //       Don't want to leak old h...
        return 0;
    }

    // Set output header.
    vector->capacity = capacity;
    vector->count = count;

    return vector;
}

inline void CHDS_Vector_reserve(void** v, size_t capacity, size_t element_size)
{
    CHDS_VectorHeader* h = 0;
    if (*v)
    {
        h = CHDS_Vector_header(*v);
    }

    h = CHDS_Vector_set_capacity(h, capacity, element_size);

    *v = h + 1;
}

inline void CHDS_Vector_grow_if_needed(void** v, size_t element_size)
{
    CHDS_VectorHeader* h = 0;
    size_t capacity = 1;

    if (*v)
    {
        h = CHDS_Vector_header(*v);
        if (h->count < h->capacity) return;

        // Determine how much to grow the vector by.
        size_t extra = (h->capacity * CHDS_VECTOR_GROWTH_FACTOR);
        if (extra == 0) extra = 1;

        capacity = h->capacity + extra;
    }
    
    h = CHDS_Vector_set_capacity(h, capacity, element_size);
    
    // Set the input array to the new ptr.
    *v = h + 1;
}

#endif