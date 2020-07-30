#include <stdio.h>

#include "Bstring.h"


void bs_print ( Bstring *bs ) {
    if ( bs_is_ptr(bs) ) {
        printf("heap - is_refer: %d, size: %zu, capacity: %zu\n",
            bs_is_refer(bs), bs_size(bs), bs_capacity(bs));
    } else {
        printf("stack - size: %zu, capacity: %zu\n",
            bs_size(bs), bs_capacity(bs));
    }
    printf("[%s]\n", bs_data(bs));
}
int main()
{
    Bstring data;
    bs_new(&data, "(((_(((data)))_)))");

    Bstring copy;
    bs_copy(&copy, &data);
    
    bs_print(&copy);
    bs_trim(&copy, "()");
    bs_print(&copy);
    
    bs_print(&data);
    bs_trim(&data, "()");
    bs_print(&data);

    bs_print(&copy);
    bs_trim(&copy, "()");
    bs_print(&copy);
    bs_free(&copy);

    return 0;
}