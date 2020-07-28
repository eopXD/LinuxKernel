#include "xs.h"

/* Better string */
typedef struct Bstring {
    xs x;
    int *ref_count;
} Bstring;

/* utility */
static inline bool bs_is_ptr ( const Bstring *bs ) {
	return xs_is_ptr(&bs->x);
}
static inline char* bs_data ( Bstring *bs ) {
	return xs_data(&bs->x);
}

/* allocate/free */
Bstring* bs_new ( Bstring *bs, const void *p ) {
	bs->x = *xs_new(&xs_literal_empty(), p);
	bs->ref_count = 0;
	return bs;
}

void bs_free ( Bstring *bs ) {
	xs_free(&bs->x);
}

/* basic function */
//void bs_copy ( Bstring *src, Bstring *dest );
//void bs_concat ( Bstring *bs, Bstring *prefix, Bstring *suffix );
//void bs_trim ( Bstring *bs, const char *trimset );

/* modify value in pos to c */
//void bs_modify_char ( Bstring *bs, int pos, char c );

/* advance */
//void bs_strtok ();
//void bs_strtok_r ();