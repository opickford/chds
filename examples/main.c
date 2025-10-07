#include <chds/vec.h>

#include <stdio.h>

int main()
{
    const int N = 100;

    chds_vec(int) v = 0;
    chds_vec_reserve(v, N);

    for (int i = 0; i < N; ++i)
    {
        chds_vec_push_back(v, i);
    }

    for (int i = 0; i < N; ++i)
    {
        printf("%d) %d\n", i, v[i]);
    }

    printf("Size: %zu\n", chds_vec_size(v));
    printf("Capacity: %zu\n", chds_vec_capacity(v));

    chds_vec_destroy(v);

    return 0;
}