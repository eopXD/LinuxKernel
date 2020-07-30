#include "xs.h"

#include <assert.h>

/* Better string */
typedef struct Bstring {
    xs x;
    int *ref_count;
} Bstring;

/* utility */
static inline bool bs_is_ptr ( const Bstring *bs ) {
	return xs_is_ptr(&bs->x);
}
static inline size_t bs_ref_count ( const Bstring *bs ) {
	return *(bs->ref_count);
}
static inline bool bs_is_refer ( Bstring *bs ) {
	if ( !bs_is_ptr(bs) ) {
		assert(bs->x.is_refer == false);
		return 0;
	}
	if ( bs_ref_count(bs) == 0 ) { // dynamic update
		bs->x.is_refer = false;
	}
	return xs_is_refer(&bs->x);
}

static inline char* bs_data ( Bstring *bs ) {
	return xs_data(&bs->x);
}
static inline size_t bs_size ( const Bstring *bs ) {
	return xs_size(&bs->x);
}
static inline size_t bs_capacity ( const Bstring *bs ) {
	return xs_capacity(&bs->x);
}

/* reference counting */
int* ref_init ( Bstring *bs ) {
	bs->ref_count = (int *) malloc(sizeof(int));
	*(bs->ref_count) = 0;
	return bs->ref_count;
}
int ref_add1 ( Bstring *bs ) {
	*(bs->ref_count) += 1; 
	return *(bs->ref_count);
}
int ref_minus1 ( Bstring *bs ) {
	assert(bs->ref_count != 0);
	*(bs->ref_count) -= 1;
	return *(bs->ref_count);
}


/* allocate/free */
Bstring* bs_new ( Bstring *bs, const void *p ) {
	bs->x = *xs_new(&xs_literal_empty(), p);
	if ( xs_is_ptr(&bs->x) ) {
		ref_init(bs);
	}
	return bs;
}

void bs_free ( Bstring *bs ) {
	if ( bs_is_ptr(bs) ) {
		if ( bs_ref_count(bs) == 0 ) {
			xs_free(&bs->x);
			free(bs->ref_count);
			return ;
		}
		*(bs->ref_count) -= 1;
	}
}

/* basic function */
Bstring* bs_copy ( Bstring *dest, Bstring *src ) {
	if ( bs_is_ptr(src) ) {
		dest->x.is_ptr = true;
		dest->x.is_refer = true;
		dest->x.ptr = src->x.ptr;
		dest->x.size = bs_size(src);
		ref_add1(src);
		dest->ref_count = src->ref_count;
	} else {
		dest->x.is_ptr = false;
		memcpy(bs_data(dest), bs_data(src), bs_size(src));
		dest->x.space_left = 15 - bs_size(src);
	}
	return dest;
}

Bstring* bs_concat ( Bstring *bs, Bstring *prefix, Bstring *suffix ) {
	size_t pres = bs_size(prefix), sufs = bs_size(suffix);
	size_t origs = bs_size(bs), capacity = bs_capacity(bs);

	char *pre = bs_data(prefix), *suf = bs_data(suffix);
	char *orig = bs_data(bs);
	char *data = orig;

	if ( origs + pres + sufs <= capacity ) {
		if ( bs_is_ptr(bs) && bs_is_refer(bs) ) {
			if ( bs_is_refer(bs) ) {
				ref_minus1(bs);
				data = bs->x.ptr = (char *) malloc(sizeof(char) * capacity);				
			}
			bs->x.size = pres + origs + sufs;
		} else {
			bs->x.space_left = 15 - pres - origs - sufs;
		}
		memmove(data + pres, orig, origs);		
		memmove(data, pre, pres);
		memmove(data + pres + origs, suf, sufs+1); // +1 for '\0'
	} else {
		xs tmp = xs_literal_empty();
		xs_grow(&tmp, pres + origs + sufs);
		tmp.size = pres + origs + sufs;
		
		data = xs_data(&tmp);
		memmove(data + pres, orig, origs);
		memmove(data, pre, pres);
		memmove(data + pres + origs, suf, sufs+1); // +1 for '\0'

		bs_free(bs);
		bs->x = tmp; // by value
	}
	ref_init(bs);
	bs->x.is_refer = false;
	return bs;
}
//void bs_trim ( Bstring *bs, const char *trimset );

/* modify value in pos to c */
//void bs_modify_char ( Bstring *bs, int pos, char c );

/* advance */
//void bs_strtok ();
//void bs_strtok_r ();