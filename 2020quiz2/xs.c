#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "xs.h"

/* reference counter */
struct RefCounter {
    int ref_size, ref_capacity;
    /* array to references */
    xs **ref_ar;
};
/* real string */
struct XString {
    xs *x;
    RefCounter refCount;
};



int main()
{
    xs string = *xs_tmp("\n foobarbar \n\n\n");
    xs_trim(&string, "\n ");
    printf("[%s] : %2zu\n", xs_data(&string), xs_size(&string));

    xs prefix = *xs_tmp("((("), suffix = *xs_tmp(")))");
    xs_concat(&string, &prefix, &suffix);
    printf("[%s] : %2zu\n", xs_data(&string), xs_size(&string));

    return 0;
}