#ifndef CHDS_VEC_H
#define CHDS_VEC_H

#include "chds.h"

#include <stdint.h>
#include <malloc.h>

// TODO: In the future could add some macro to remove make #define to remove the lib prefix.

/*

HEADER

*/

#ifndef CHDS_VEC_GROWTH_FACTOR
#define CHDS_VEC_GROWTH_FACTOR 2
#endif

/*

INTERNAL

*/

typedef struct
{
    size_t size;         // Number of elements stored in the chds_vec.
    size_t capacity;     // Number of elements the chds_vec can store.

} CHDS_VecHeader;


// Returns a pointer to the vector's header.
#define chds_vec__header(v) ((CHDS_VecHeader*)(v) - 1)

inline static CHDS_Result chds_vec__set_capacity(CHDS_VecHeader** h, size_t capacity, size_t element_size);
inline static CHDS_Result chds_vec__reserve(void** v, size_t capacity, size_t element_size);
inline static CHDS_Result chds_vec__resize(void** v, size_t capacity, size_t element_size);
inline static CHDS_Result chds_vec__grow_if_needed(void** v, size_t element_size);

/*

PUBLIC API

*/

/**
* Declare a typed vector.
*/
#define CHDS_Vec(T) T*

/**
* Returns the number of elements in the vector.
* 
*/
#define chds_vec_size(v) ((v) ? chds_vec__header((v))->size : 0)

/**
* Returns the number of elements the vector has allocated memory for.
*/
#define chds_vec_capacity(v) ((v) ? chds_vec__header((v))->capacity : 0)

/**
* 
* Push a value into the back of the vector.
* 
* @param v The vector. Must not be NULL.
* @param value The value to push.
* 
* @return CHDS_OK on success, CHDS_ERR_ALLOC on allocation failure.
* 
*/
#define chds_vec_push(v, value) do \
{ \
    chds_vec__grow_if_needed(&(v), sizeof(*v));                                \
    (v)[chds_vec__header((v))->size++] = (value);                              \
\
} while (0)

/**
* 
* Ensure the vector has capacity to hold the given number of elements.
* Note, this Will not shrink the vector.
* 
* @param v The vector.
* 
* @return CHDS_OK on success, CHDS_ERR_ALLOC on allocation failure.
* 
*/
#define chds_vec_reserve(v, capacity) chds_vec__reserve(&(v), capacity, sizeof(*v))

/**
*
* Sets the capacity of the vector.
*
* @param v The vector.
*
* @return CHDS_OK on success, CHDS_ERR_ALLOC on allocation failure.
*
*/
#define chds_vec_resize(v, capacity) chds_vec__resize(&(v), capacity, sizeof(*v))

/**
*
* Sets the vector's size to 0.
*
* @param v The vector.
*
*/
#define chds_vec_clear(v) if ((v)) { chds_vec__header((v))->size = 0; }

/**
*
* Return 1 if the vector is empty, 0 otherwise.
*
* @param v The vector.
*
*/
#define chds_vec_empty(v) (chds_vec_size((v)) == 0)

/**
* 
* Releases the underlying vector array.
* 
*/
inline void chds_vec_destroy(void* v)
{
    // TODO: Free elements individually? Would require dtor func.
    if (v) free(chds_vec__header(v));
}

/*

INTERNAL IMPLEMENTATION

*/

inline static CHDS_Result chds_vec__set_capacity(CHDS_VecHeader** h, size_t capacity, size_t element_size)
{
    // Copy old header data if it exists.
    size_t count = 0;
    if (*h)
    {
        count = (*h)->size;

        // Capacity does not need to change.
        if (capacity == (*h)->capacity) return CHDS_OK;
    }

    size_t size = sizeof(CHDS_VecHeader) + capacity * element_size;

    CHDS_VecHeader* new_h = realloc(*h, size);
    if (!new_h) return CHDS_ERR_ALLOC;

    // Copy data to new header.
    new_h->capacity = capacity;
    new_h->size = count;

    *h = new_h;

    return CHDS_OK;
}

inline static CHDS_Result chds_vec__reserve(void** v, size_t capacity, size_t element_size)
{
    CHDS_VecHeader* h = 0;
    if (*v)
    {
        h = chds_vec__header(*v);

        // Reserve should not shrink the chds_vec.
        if (capacity <= h->capacity) return CHDS_OK;
    }

    CHDS_Result res = chds_vec__set_capacity(&h, capacity, element_size);
    if (res != CHDS_OK) return res;
    
    *v = h + 1;
    return CHDS_OK;
}

inline static CHDS_Result chds_vec__resize(void** v, size_t capacity, size_t element_size)
{
    CHDS_VecHeader* h = (*v) ? chds_vec__header(*v) : 0;
    CHDS_Result res = chds_vec__set_capacity(&h, capacity, element_size);
    if (res != CHDS_OK) return res;

    // Clamp the size to the new capacity.
    if (h->size > h->capacity) h->size = h->capacity;

    *v = h + 1;

    return CHDS_OK;
}

inline static CHDS_Result chds_vec__grow_if_needed(void** v, size_t element_size)
{
    CHDS_VecHeader* h = 0;
    size_t capacity = 1;

    if (*v)
    {
        h = chds_vec__header(*v);
        if (h->size < h->capacity) return CHDS_OK;

        // Determine how much to grow the chds_vec by.
        size_t extra = (size_t)(h->capacity * CHDS_VEC_GROWTH_FACTOR);
        if (extra == 0) extra = 1;

        capacity = h->capacity + extra;
    }
    
    CHDS_Result res = chds_vec__set_capacity(&h, capacity, element_size);
    if (res != CHDS_OK) return res;
    
    // Update the input arr pointer.
    *v = h + 1;

    return CHDS_OK;
}

#endif