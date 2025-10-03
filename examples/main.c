#include <chds/vector.h>

#include <stdio.h>

int main()
{
    const int N = 100;

    Vector(int) v = 0;
    Vector_reserve(v, N);

    for (int i = 0; i < N; ++i)
    {
        Vector_push_back(v, i);
    }

    for (int i = 0; i < N; ++i)
    {
        printf("%d) %d\n", i, v[i]);
    }

    printf("Size: %zu\n", Vector_size(v));

    Vector_destroy(v);

    return 0;
}