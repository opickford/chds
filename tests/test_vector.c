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

#include <stdio.h>

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

    assert(Vector_size(v) == 0);

    Vector_destroy(v);
}

void test_vector()
{
    test_size();
    test_push_back();
    test_reserve();
}