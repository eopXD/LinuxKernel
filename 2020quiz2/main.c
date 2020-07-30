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
    Bstring prefix, suffix;
    
    bs_new(&prefix, "prefix");
    bs_new(&suffix, "suffix");

    Bstring stk;
    bs_new(&stk, "stk");
    bs_print(&stk);
    bs_concat(&stk, &prefix, &suffix);
    bs_print(&stk);

    Bstring hp;
    bs_new(&hp, "to heap");
    bs_print(&hp);
    bs_concat(&hp, &prefix, &suffix);
    bs_print(&hp);
    

    Bstring origin_cap;
    bs_new(&origin_cap, "This a long string");
    Bstring expand_cap;
    bs_new(&expand_cap, "We need to expand capacity");
    

    bs_print(&origin_cap);
    bs_concat(&origin_cap, &prefix, &suffix);
    bs_print(&origin_cap);
    
    Bstring copy;
    bs_copy(&copy, &expand_cap);

    bs_print(&copy);
    bs_concat(&copy, &prefix, &suffix);
    bs_print(&copy);

    bs_print(&expand_cap);
    bs_concat(&expand_cap, &prefix, &suffix);
    bs_print(&expand_cap);


    bs_free(&origin_cap);
    bs_free(&expand_cap);

    return 0;
}