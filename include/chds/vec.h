#ifndef CHDS_VEC_H
#define CHDS_VEC_H

#include <stdint.h>
#include <stdlib.h>

#ifndef CHDS_VEC_GROWTH_FACTOR
#define CHDS_VEC_GROWTH_FACTOR 1.5f
#endif

// TODO: In the future could add some macro to remove make #define to remove the lib prefix.

// TODO: Is it nicer to just use a struct and void*? the only issue is losing the type information. but everything else would potentially
//       be clearer. Using a struct will introduce one pointer indirection, however, that is obviously a minimal issue. For now I think this is fine?
//       however in my code i normally just write a pointer to the void* array like int* data = vec.data;

// TODO: I feel like we should be handling if chds_vec_header returns 0?

typedef struct
{
    size_t size;         // Number of elements stored in the chds_vec.
    size_t capacity;     // Number of elements the chds_vec can store.

} chds_vec_header;

// TODO: tests for all functionality.

// TODO: Proper commenting of everything.

// Define a chds_vec type.
// TODO: Rename chds_vec_t?
#define CHDS_VEC(T) T*

// TODO: Make private.
// Return the vector header.
#define CHDS_VEC_HEADER(v) ((chds_vec_header*)(v) - 1)

// Return the number of elements in the vector.
#define CHDS_VEC_SIZE(v) (v ? CHDS_VEC_HEADER((v))->size : 0)

// Return the number of elements the vector has allocated memory for.
#define CHDS_VEC_CAPACITY(v) (v ? CHDS_VEC_HEADER((v))->capacity : 0)

// Add a value to the vector.
#define CHDS_VEC_PUSH_BACK(v, value) do \
{ \
    chds_vec__grow_if_needed(&(v), sizeof(*v)); \
    (v)[CHDS_VEC_HEADER((v))->size++] = (value); \
\
} while (0)

// Increases the capacity of the chds_vec to hold the given number of elements.
// Note, this will not shrink the chds_vec.
#define CHDS_VEC_RESERVE(v, capacity) chds_vec__reserve(&(v), capacity, sizeof(*v))

// Sets the capacity of the vector.
// Note, this can shrink the vector.
#define CHDS_VEC_RESIZE(v, capacity) chds_vec__resize(&(v), capacity, sizeof(*v))

// Clears the vector, afterwards, size == 0. 
#define CHDS_VEC_CLEAR(v) if (v) { CHDS_VEC_HEADER((v))->size = 0; }

// Releases the underlying vector array.
inline void chds_vec_destroy(void* v)
{
    // TODO: Free elements individually? Would require dtor func.
    if (v) free(CHDS_VEC_HEADER(v));
}

// TODO: Private methods. Could be hidden by actually turning into lib rather than header only.
inline chds_vec_header* chds_vec__set_capacity(chds_vec_header* h, size_t capacity, size_t element_size)
{
    // Copy old header data.
    size_t count = 0;
    if (h)
    {
        count = h->size;

        if (capacity == h->capacity) return h;
    }

    size_t size = sizeof(chds_vec_header) + capacity * element_size;

    chds_vec_header* chds_vec = realloc(h, size);
    if (!chds_vec)
    {
        // TODO: How can we possibly handle failure?
        //       Don't want to leak old h...
        return 0;
    }

    // Set output header.
    chds_vec->capacity = capacity;
    chds_vec->size = count;

    return chds_vec;
}

inline void chds_vec__reserve(void** v, size_t capacity, size_t element_size)
{
    chds_vec_header* h = 0;
    if (*v)
    {
        h = CHDS_VEC_HEADER(*v);

        // Reserve should not shrink the chds_vec.
        if (capacity <= h->capacity) return;
    }

    h = chds_vec__set_capacity(h, capacity, element_size);

    *v = h + 1;
}

inline void chds_vec__resize(void** v, size_t capacity, size_t element_size)
{
    chds_vec_header* h = 0;
    if (*v)
    {
        h = CHDS_VEC_HEADER(*v);
    }

    h = chds_vec__set_capacity(h, capacity, element_size);

    // Ensure the previous size does not exceed the new capacity.
    if (h->size > h->capacity) h->size = h->capacity;

    *v = h + 1;
}

inline void chds_vec__grow_if_needed(void** v, size_t element_size)
{
    chds_vec_header* h = 0;
    size_t capacity = 1;

    if (*v)
    {
        h = CHDS_VEC_HEADER(*v);
        if (h->size < h->capacity) return;

        // Determine how much to grow the chds_vec by.
        size_t extra = (size_t)(h->capacity * CHDS_VEC_GROWTH_FACTOR);
        if (extra == 0) extra = 1;

        capacity = h->capacity + extra;
    }
    
    h = chds_vec__set_capacity(h, capacity, element_size);
    
    // Set the input array to the new ptr.
    *v = h + 1;
}

#endif