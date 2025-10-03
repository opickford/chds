#include "test_vector.h"

#include <chds/vector.h>

#include <assert.h>

static void test_vector_push_back()
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

void test_vector()
{
    test_vector_push_back();
}