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
static inline bool bs_is_refer ( const Bstring *bs ) {
	return xs_is_refer(&bs->x);
}
static inline bool bs_is_src ( const Bstring *bs ) {
	return xs_is_src(&bs->x);
}
static inline char* bs_data ( Bstring *bs ) {
	return xs_data(&bs->x);
}
static inline size_t bs_size ( const Bstring *bs ) {
	return xs_size(&bs->x);
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

/* reference counting */
int ref_add ( Bstring *bs ) {
	if ( bs_is_src(bs) ) {
		*(bs->ref_count) += 1;
	} else {
		bs->ref_count = (int *)malloc(sizeof(int));
		*(bs->ref_count) = 1;
		bs->x.is_src = true;
	}
	return *(bs->ref_count);
}

/* basic function */
Bstring* bs_copy ( Bstring *dest, Bstring *src ) {
	if ( bs_is_ptr(src) ) {
		dest->x.is_ptr = true;
		dest->x.is_refer = true;
		dest->x.ptr = src->x.ptr;
		dest->x.size = bs_size(src);
		ref_add(src);
		dest->ref_count = src->ref_count;
	} else {
		dest->x.is_ptr = false;
		memcpy(bs_data(dest), bs_data(src), bs_size(src));
		dest->x.space_left = 15 - bs_size(src);
	}
	return dest;
}

//void bs_concat ( Bstring *bs, Bstring *prefix, Bstring *suffix );
//void bs_trim ( Bstring *bs, const char *trimset );

/* modify value in pos to c */
//void bs_modify_char ( Bstring *bs, int pos, char c );

/* advance */
//void bs_strtok ();
//void bs_strtok_r ();