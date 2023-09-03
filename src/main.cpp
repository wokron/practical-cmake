#include <stdio.h>
#include "add.h"

int main()
{
    int a = 1, b = 2;
    printf("a = %d, b = %d\n", a, b);

    int c = add(a, b);
    printf("a + b = %d\n", c);

    return 0;
}
