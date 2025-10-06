#ifndef VECTOR_H
#define VECTOR_H

#include <stdint.h>
#include <stdlib.h>

#define CHDS_VECTOR_GROWTH_FACTOR 1.5f

// TODO: Is it nicer to just use a struct and void*? the only issue is losing the type information. but everything else would potentially
//       be clearer. Using a struct will introduce one pointer indirection, however, that is obviously a minimal issue. For now I think this is fine?
//       however in my code i normally just write a pointer to the void* array like int* data = vec.data;

// TODO: Should we name stuff Vec to save typing?? Vector is kinda unnecessary.

// TODO: I feel like we should be handling if CHDS_Vector_header returns 0?

typedef struct
{
    size_t size;         // Number of elements stored in the vector.
    size_t capacity;     // Number of elements the vector can store.

} CHDS_VectorHeader;

// TODO: tests for all functionality.

// Define a vector type.
#define Vector(T) T*

// TODO: Make private.
// Return the vector header.
#define CHDS_Vector_header(v) ((CHDS_VectorHeader*)(v) - 1)

// Return the number of elements in the vector.
#define Vector_size(v) (v ? CHDS_Vector_header((v))->size : 0)

// Return the number of elements the vector has allocated memory for.
#define Vector_capacity(v) (v ? CHDS_Vector_header((v))->capacity : 0)

// Add a value to the vector.
#define Vector_push_back(v, value) do \
{ \
    CHDS_Vector_grow_if_needed(&(v), sizeof(*v)); \
    (v)[CHDS_Vector_header((v))->size++] = (value); \
\
} while (0)

// Increases the capacity of the vector to hold the given number of elements.
// Note, this will not shrink the vector.
#define Vector_reserve(v, capacity) CHDS_Vector_reserve(&(v), capacity, sizeof(*v))

// Clears the vector, afterwards, size == 0. 
#define Vector_clear(v) if (v) { CHDS_Vector_header((v))->size = 0; }

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
        count = h->size;

        if (capacity == h->capacity) return h;
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
    vector->size = count;

    return vector;
}

inline void CHDS_Vector_reserve(void** v, size_t capacity, size_t element_size)
{
    CHDS_VectorHeader* h = 0;
    if (*v)
    {
        h = CHDS_Vector_header(*v);

        // Reserve should not shrink the vector.
        if (capacity <= h->capacity) return;
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
        if (h->size < h->capacity) return;

        // Determine how much to grow the vector by.
        size_t extra = (size_t)(h->capacity * CHDS_VECTOR_GROWTH_FACTOR);
        if (extra == 0) extra = 1;

        capacity = h->capacity + extra;
    }
    
    h = CHDS_Vector_set_capacity(h, capacity, element_size);
    
    // Set the input array to the new ptr.
    *v = h + 1;
}

#endif