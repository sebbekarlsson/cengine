#include "include/random.h"
#include <time.h>
#include <stdlib.h>

void random_init()
{
    srand(time(0));
}

int get_random_int(int start, int end)
{
    return rand() % (end + 1 - start) + start;
}
