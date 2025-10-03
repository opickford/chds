#include <chds/vector.h>

#include <stdio.h>

int main()
{
    Vector(int) v = 0;

    for (int i = 0; i < 100; ++i)
    {
        Vector_push_back(v, i);
    }

    for (int i = 0; i < 100; ++i)
    {
        printf("%d) %d\n", i, v[i]);
    }

    printf("Size: %zu\n", Vector_size(v));

    Vector_destroy(v);

    return 0;
}