#include <chds/vec.h>

#include <stdio.h>

int main()
{
    const int N = 100;

    CHDS_VEC(int) v = 0;
    CHDS_VEC_RESERVE(v, N);

    for (int i = 0; i < N; ++i)
    {
        CHDS_VEC_PUSH_BACK(v, i);
    }

    for (int i = 0; i < N; ++i)
    {
        printf("%d) %d\n", i, v[i]);
    }

    printf("Size: %zu\n", CHDS_VEC_SIZE(v));
    printf("Capacity: %zu\n", CHDS_VEC_CAPACITY(v));

    chds_vec_destroy(v);

    return 0;
}