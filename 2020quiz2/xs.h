#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef union {
    /* allow strings up to 15 bytes to stay on the stack
     * use the last byte as a null terminator and to store flags
     * much like fbstring:
     * https://github.com/facebook/folly/blob/master/folly/docs/FBString.md
     */
    char data[16];

    struct {
        uint8_t filler[15],
            /* how many free bytes in this stack allocated string
             * same idea as fbstring
             */
            space_left : 4,
            /* if it is on heap, set to 1 */
            is_ptr : 1, 
            /* if refer to other, set to 1 */
            is_refer : 1, 
            /* if is source, set to 1 */
            flag2 : 1,
            flag3 : 1;
    };

    /* heap allocated */
    struct {
        char *ptr;
        /* supports strings up to 2^54 - 1 bytes */
        size_t size : 54,
            /* capacity is always a power of 2 (unsigned)-1 */
            capacity : 6;
        /* the last 4 bits are important flags */
    };
} xs;
static inline bool xs_is_refer(const xs *x) { return x->is_refer; }
static inline bool xs_is_ptr(const xs *x) { return x->is_ptr; }
static inline size_t xs_size(const xs *x)
{
    return xs_is_ptr(x) ? x->size : 15 - x->space_left;
}
static inline char *xs_data(const xs *x)
{
    return xs_is_ptr(x) ? (char *) x->ptr : (char *) x->data;
}
static inline size_t xs_capacity(const xs *x)
{
    return xs_is_ptr(x) ? ((size_t) 1 << x->capacity) - 1 : 15;
}

#define xs_literal_empty() \
    (xs) { .space_left = 15 }

static inline int ilog2(uint32_t n) { return 32 - __builtin_clz(n) - 1; }

xs *xs_new(xs *x, const void *p)
{
    *x = xs_literal_empty();
    x->is_refer = false;
    size_t len = strlen(p) + 1;
    if (len > 16) {
        x->is_ptr = true;
        x->capacity = ilog2(len) + 1;
        x->size = len - 1;
        x->ptr = malloc((size_t) 1 << x->capacity);
        memcpy(x->ptr, p, len);
    } else {
        x->is_ptr = false;
        memcpy(x->data, p, len);
        x->space_left = 15 - (len - 1);
    }
    return x;
}

/* grow up to specified size */
char* xs_grow(xs *x, size_t len)
{
    if (len <= xs_capacity(x))
        return x->ptr;
    len = ilog2(len) + 1;
    if (xs_is_ptr(x))
        x->ptr = realloc(x->ptr, (size_t) 1 << len);
    else {
        char buf[16];
        memcpy(buf, x->data, 16);
        x->ptr = malloc((size_t) 1 << len);
        memcpy(x->ptr, buf, 16);
    }
    x->is_ptr = true;
    x->capacity = len;
    return x->ptr;
}

static inline xs *xs_newempty(xs *x)
{
    *x = xs_literal_empty();
    x->is_ptr = x->is_refer = false;
    return x;
}

static inline xs *xs_free(xs *x)
{
    if ( xs_is_ptr(x) ) {
        printf("data freed: [%s]\n", xs_data(x));
        free(xs_data(x));
    }
    return xs_newempty(x);
}