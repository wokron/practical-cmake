#include <stdio.h>
#include "add/add.h"
#include "fibo/fibo.h"

int main()
{
    int a = 1, b = 2;
    printf("a = %d, b = %d\n", a, b);

    int c = add(a, b);
    printf("a + b = %d\n", c);

    for (int i = 1; i <= 10; i++)
    {
        printf("fibo(%d) = %d\n", i, fibonacci(i));
    }

    return 0;
}
