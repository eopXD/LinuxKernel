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
