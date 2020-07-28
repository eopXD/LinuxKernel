#include <stdio.h>

#include "Bstring.h"

int main()
{
    Bstring none;
    bs_new(&none, "");
    printf("%d, %d, %s\n", bs_is_ptr(&none), bs_is_refer(&none), bs_data(&none));
    
    Bstring short_str;
    bs_new(&short_str, "short string");
    printf("%d, %d, %s\n", bs_is_ptr(&short_str), bs_is_refer(&short_str), bs_data(&short_str));
    
    Bstring long_str;
    bs_new(&long_str, "a long enough string");
    printf("%d, %d, %s\n", bs_is_ptr(&long_str), bs_is_refer(&long_str), bs_data(&long_str));
    
    Bstring copy_short;
    bs_copy(&copy_short, &short_str);
    printf("%d, %d, %s\n", bs_is_ptr(&copy_short), bs_is_refer(&copy_short), bs_data(&copy_short));
    
    Bstring copy_long;
    bs_copy(&copy_long, &long_str);
    printf("%d, %d, %s\n", bs_is_ptr(&copy_long), bs_is_refer(&copy_long), bs_data(&copy_long));
    
    bs_free(&none);
    bs_free(&short_str);
    bs_free(&long_str);
    bs_free(&copy_short);
    bs_free(&copy_long);
    return 0;
}