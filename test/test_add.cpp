#include "add/add.h"
#include <assert.h>

int main()
{
    assert(add(1, 2) == 3);
    assert(add(1, -1) == 0);
    assert(add(1, -2) == -1);
    assert(add(100, 100) == 200);
    return 0;
}
