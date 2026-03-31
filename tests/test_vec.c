#include <chds/vec.h>

#include <stdio.h>

#define CHDS_ASSERT(expr) do \
if (!(expr)) \
{  \
    fprintf(stderr, "Assertion failed: %s\n"    \
                    "  in file %s, line %d\n",  \
            #expr, __FILE__, __LINE__);         \
    exit(1);                                    \
} \
while(0)

static void test_size()
{
    CHDS_Vec(int) v = 0;

    CHDS_ASSERT(chds_vec_size(v) == 0);

    CHDS_ASSERT(chds_vec_push(v, 1) == CHDS_OK);
    CHDS_ASSERT(chds_vec_size(v) == 1);

    CHDS_ASSERT(chds_vec_push(v, 2) == CHDS_OK);
    CHDS_ASSERT(chds_vec_size(v) == 2);

    chds_vec_destroy(v);
    CHDS_ASSERT(v == 0);
}

static void test_push()
{
    CHDS_Vec(int) v = 0;

    CHDS_ASSERT(chds_vec_push(v, 1) == CHDS_OK);
    CHDS_ASSERT(chds_vec_push(v, 2) == CHDS_OK);
    CHDS_ASSERT(chds_vec_push(v, 3) == CHDS_OK);

    CHDS_ASSERT(v[0] == 1);
    CHDS_ASSERT(v[1] == 2);
    CHDS_ASSERT(v[2] == 3);
    CHDS_ASSERT(chds_vec_size(v) == 3);

    chds_vec_destroy(v);
    CHDS_ASSERT(v == 0);
}

static void test_pop()
{
    CHDS_Vec(int) v = 0;

    CHDS_ASSERT(chds_vec_push(v, 1) == CHDS_OK);
    CHDS_ASSERT(chds_vec_push(v, 2) == CHDS_OK);

    CHDS_ASSERT(chds_vec_size(v) == 2);

    chds_vec_pop(v);

    CHDS_ASSERT(chds_vec_size(v) == 1);

    chds_vec_pop(v);

    CHDS_ASSERT(chds_vec_size(v) == 0);

    chds_vec_destroy(v);
    CHDS_ASSERT(v == 0);
}

static void test_reserve()
{
    const int CAPACITY = 5;

    CHDS_Vec(int) v = 0;
    CHDS_ASSERT(CHDS_OK == chds_vec_reserve(v, CAPACITY));

    {
        CHDS_VecHeader* h = chds_vec__header(v);
        CHDS_ASSERT(h);
        CHDS_ASSERT(h->capacity == CAPACITY);
    }

    // Attempt to reserve less elements, this should not shrink the chds_vec.
    CHDS_ASSERT(chds_vec_reserve(v, 3) == CHDS_OK);
    CHDS_ASSERT(chds_vec_capacity(v) == CAPACITY);

    CHDS_ASSERT(chds_vec_size(v) == 0);

    chds_vec_destroy(v);
    CHDS_ASSERT(v == 0);
}

static void test_resize()
{
    const int CAPACITY = 5;

    CHDS_Vec(int) v = 0;
    CHDS_ASSERT(chds_vec_resize(v, CAPACITY) == CHDS_OK);

    for (int i = 0; i < CAPACITY; ++i)
    {
        CHDS_ASSERT(chds_vec_push(v, i) == CHDS_OK);
    }

    CHDS_ASSERT(chds_vec_size(v) == CAPACITY);
    CHDS_ASSERT(chds_vec_capacity(v) == CAPACITY);
    
    // Resize to less than current capacity, this should shrink the chds_vec
    // and also reduce the size to the capacity.
    CHDS_ASSERT(chds_vec_resize(v, 3) == CHDS_OK);
    CHDS_ASSERT(chds_vec_capacity(v) == 3);
    CHDS_ASSERT(chds_vec_size(v) == 3);

    chds_vec_destroy(v);
}

static void test_clear()
{
    CHDS_Vec(int) v = 0;

    CHDS_ASSERT(chds_vec_push(v, 1) == CHDS_OK);
    CHDS_ASSERT(chds_vec_push(v, 2) == CHDS_OK);
    CHDS_ASSERT(chds_vec_push(v, 3) == CHDS_OK);

    CHDS_ASSERT(chds_vec_size(v) == 3);

    chds_vec_clear(v);
    CHDS_ASSERT(chds_vec_size(v) == 0);
    CHDS_ASSERT(chds_vec_capacity(v) > 0);
}

static void test_null()
{
    // Define null vector.
    CHDS_Vec(int) v = 0;

    // Test the defined behaviour for a null vector.
    CHDS_ASSERT(chds_vec_size(v) == 0);
    CHDS_ASSERT(chds_vec_capacity(v) == 0);
    CHDS_ASSERT(chds_vec_empty(v));

    // Should not throw an error.
    chds_vec_clear(v); 
    chds_vec_destroy(v);
    CHDS_ASSERT(v == 0);

    // The rest of the functions are tested from null in the other tests.
}

int main()
{
    test_size();
    // TODO: test_capacity()?
    test_push();
    test_pop();
    test_reserve();
    test_resize();
    test_clear();
    test_null();

    return 0;
}