#include "add/add.h"
#include <assert.h>

int fibonacci(int n)
{
    assert(n > 0);
    if (n == 1 || n == 2)
        return 1;
    return add(fibonacci(n-1), fibonacci(n-2));
}
