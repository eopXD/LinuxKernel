#include "xs.h"

/* Better string */
typedef struct Bstring {
    xs x;
    size_t ref_size: 54, ref_capacity: 6;
    struct Bstring **ref_ar;
} Bstring;

/* utility */
static inline bool bs_is_ptr ( const Bstring *bs ) {
	return xs_is_ptr(&bs->x);
}
static inline char *bs_data ( Bstring *bs ) {
	return xs_data(&bs->x);
}
static inline void bs_ref_init ( Bstring *bs ) {
	bs->ref_size = 0;
	bs->ref_capacity = 0;
	bs->ref_ar = 0;
}
/* allocate/free */
void bs_newempty ( Bstring *bs ) {
	xs_newempty(&bs->x);
	bs_ref_init(bs);
}
void bs_new ( Bstring *bs, const void *p ) {
	xs_new(&bs->x,p);
	bs_ref_init(bs);
}

void bs_free ( Bstring *bs ) {
	xs_free(&bs->x);
	if ( bs->ref_ar )
		free(bs->ref_ar);
}

/* basic function */
// usage: dest is a pointer, not allocated yet
//void bs_copy ( Bstring *src, Bstring *dest );
void bs_copy ( Bstring *src, Bstring *dest ) {
/* shallow copy by default */

	
}



//void bs_concat ( Bstring *bs, Bstring *prefix, Bstring *suffix );
//void bs_trim ( Bstring *bs, const char *trimset );

/* modify value in pos to c */
//void bs_modify_char ( Bstring *bs, int pos, char c );


/* advance */
//void bs_strtok ();
//void bs_strtok_r ();