#include "test_vec.h"

#include <chds/vec.h>

#include <assert.h>

static void test_size()
{
    chds_vec(int) v = 0;

    assert(chds_vec_size(v) == 0);

    chds_vec_push_back(v, 1);
    assert(chds_vec_size(v) == 1);

    chds_vec_push_back(v, 2);
    assert(chds_vec_size(v) == 2);
}

static void test_push_back()
{
    chds_vec(int) v = 0;

    chds_vec_push_back(v, 1);
    chds_vec_push_back(v, 2);
    chds_vec_push_back(v, 3);

    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(chds_vec_size(v) == 3);

    chds_vec_destroy(v);
}

static void test_reserve()
{
    const int CAPACITY = 5;

    chds_vec(int) v = 0;
    chds_vec_reserve(v, CAPACITY);

    {
        chds_vec_header_t* h = chds_vec_header(v);
        assert(h);
        assert(h->capacity == CAPACITY);
    }

    // Attempt to reserve less elements, this should not shrink the chds_vec.
    chds_vec_reserve(v, 3);
    assert(chds_vec_capacity(v) == CAPACITY);

    assert(chds_vec_size(v) == 0);

    chds_vec_destroy(v);
}

static void test_resize()
{
    const int CAPACITY = 5;

    chds_vec(int) v = 0;
    chds_vec_resize(v, CAPACITY);

    for (int i = 0; i < CAPACITY; ++i)
    {
        chds_vec_push_back(v, i);
    }

    assert(chds_vec_size(v) == CAPACITY);
    assert(chds_vec_capacity(v) == CAPACITY);
    
    // Resize to less than current capacity, this should shrink the chds_vec
    // and also reduce the size to the capacity.
    chds_vec_resize(v, 3);
    assert(chds_vec_capacity(v) == 3);
    assert(chds_vec_size(v) == 3);

    chds_vec_destroy(v);
}

static void test_clear()
{
    chds_vec(int) v = 0;

    chds_vec_push_back(v, 1);
    chds_vec_push_back(v, 2);
    chds_vec_push_back(v, 3);

    assert(chds_vec_size(v) == 3);

    chds_vec_clear(v);
    assert(chds_vec_size(v) == 0);
    assert(chds_vec_capacity(v) > 0);
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