#include "test_vector.h"

#include <chds/vector.h>

#include <assert.h>

static void test_size()
{
    Vector(int) v = 0;

    assert(Vector_size(v) == 0);

    Vector_push_back(v, 1);
    assert(Vector_size(v) == 1);

    Vector_push_back(v, 2);
    assert(Vector_size(v) == 2);
}

static void test_push_back()
{
    Vector(int) v = 0;

    Vector_push_back(v, 1);
    Vector_push_back(v, 2);
    Vector_push_back(v, 3);

    assert(v[0] == 1);
    assert(v[1] == 2);
    assert(v[2] == 3);
    assert(Vector_size(v) == 3);

    Vector_destroy(v);
}

static void test_reserve()
{
    const int CAPACITY = 5;

    Vector(int) v = 0;
    Vector_reserve(v, CAPACITY);

    {
        CHDS_VectorHeader* h = CHDS_Vector_header(v);
        assert(h);
        assert(h->capacity == CAPACITY);
    }

    // Attempt to reserve less elements, this should not shrink the vector.
    Vector_reserve(v, 3);
    {
        CHDS_VectorHeader* h = CHDS_Vector_header(v);
        assert(h);
        assert(h->capacity == CAPACITY);
    }

    assert(Vector_size(v) == 0);

    Vector_destroy(v);
}

static void test_resize()
{
    const int CAPACITY = 5;

    Vector(int) v = 0;
    Vector_resize(v, CAPACITY);

    {
        CHDS_VectorHeader* h = CHDS_Vector_header(v);
        assert(h);
        assert(h->capacity == CAPACITY);
    }

    // Resize to less than current capacity, this should shrink the vector.
    Vector_resize(v, 3);
    {
        CHDS_VectorHeader* h = CHDS_Vector_header(v);
        assert(h);
        assert(h->capacity == 3);
    }

    assert(Vector_size(v) == 0);

    Vector_destroy(v);
}

static void test_clear()
{
    Vector(int) v = 0;

    Vector_push_back(v, 1);
    Vector_push_back(v, 2);
    Vector_push_back(v, 3);

    assert(Vector_size(v) == 3);

    Vector_clear(v);
    assert(Vector_size(v) == 0);
    assert(Vector_capacity(v) > 0);
}

void test_vector()
{
    test_size();
    // TODO: test_capacity()?
    test_push_back();
    test_reserve();
    test_resize();
    test_clear();
}