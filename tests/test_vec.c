#include "test_vec.h"

#include <chds/vec.h>

#include <assert.h>

static void test_size()
{
    CHDS_VEC(int) v = 0;

    assert(CHDS_VEC_SIZE(v) == 0);

    CHDS_VEC_PUSH_BACK(v, 1);
    assert(CHDS_VEC_SIZE(v) == 1);

    CHDS_VEC_PUSH_BACK(v, 2);
    assert(CHDS_VEC_SIZE(v) == 2);
}

static void test_push_back()
{
    CHDS_VEC(int) v = 0;

    CHDS_VEC_PUSH_BACK(v, 1);
    CHDS_VEC_PUSH_BACK(v, 2);
    CHDS_VEC_PUSH_BACK(v, 3);

    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(CHDS_VEC_SIZE(v) == 3);

    chds_vec_destroy(v);
}

static void test_reserve()
{
    const int CAPACITY = 5;

    CHDS_VEC(int) v = 0;
    CHDS_VEC_RESERVE(v, CAPACITY);

    {
        chds_vec_header* h = CHDS_VEC_HEADER(v);
        assert(h);
        assert(h->capacity == CAPACITY);
    }

    // Attempt to reserve less elements, this should not shrink the chds_vec.
    CHDS_VEC_RESERVE(v, 3);
    assert(CHDS_VEC_CAPACITY(v) == CAPACITY);

    assert(CHDS_VEC_SIZE(v) == 0);

    chds_vec_destroy(v);
}

static void test_resize()
{
    const int CAPACITY = 5;

    CHDS_VEC(int) v = 0;
    CHDS_VEC_RESIZE(v, CAPACITY);

    for (int i = 0; i < CAPACITY; ++i)
    {
        CHDS_VEC_PUSH_BACK(v, i);
    }

    assert(CHDS_VEC_SIZE(v) == CAPACITY);
    assert(CHDS_VEC_CAPACITY(v) == CAPACITY);
    
    // Resize to less than current capacity, this should shrink the chds_vec
    // and also reduce the size to the capacity.
    CHDS_VEC_RESIZE(v, 3);
    assert(CHDS_VEC_CAPACITY(v) == 3);
    assert(CHDS_VEC_SIZE(v) == 3);

    chds_vec_destroy(v);
}

static void test_clear()
{
    CHDS_VEC(int) v = 0;

    CHDS_VEC_PUSH_BACK(v, 1);
    CHDS_VEC_PUSH_BACK(v, 2);
    CHDS_VEC_PUSH_BACK(v, 3);

    assert(CHDS_VEC_SIZE(v) == 3);

    CHDS_VEC_CLEAR(v);
    assert(CHDS_VEC_SIZE(v) == 0);
    assert(CHDS_VEC_CAPACITY(v) > 0);
}

void test_vec()
{
    test_size();
    // TODO: test_capacity()?
    test_push_back();
    test_reserve();
    test_resize();
    test_clear();
}