#include <stdio.h>

#include "Bstring.h"

int main()
{
    Bstring none;
    bs_new(&none, "");
    printf("%d, %s\n", bs_is_ptr(&none), bs_data(&none));
    bs_free(&none);
    puts("free none");
    
    Bstring short_str;
    bs_new(&short_str, "short string");
    printf("%d, %s\n", bs_is_ptr(&short_str), bs_data(&short_str));
    bs_free(&short_str);
    puts("free short");
    
    Bstring long_str;
    bs_new(&long_str, "a long enough string");
    printf("%d, %s\n", bs_is_ptr(&long_str), bs_data(&long_str));
    bs_free(&long_str);
    puts("free long");
    
    return 0;
}