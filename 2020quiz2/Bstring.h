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
		ref_minus1(bs);
	}
}

/* basic function */
Bstring* bs_copy ( Bstring *dest, Bstring *src ) {
	if ( dest == 0 || src == 0 ) {
		return 0;
	}
	if ( bs_is_ptr(src) ) {
		dest->x.is_ptr = true;
		dest->x.is_refer = true;
		dest->x.ptr = src->x.ptr;
		dest->x.size = bs_size(src);
		dest->x.capacity = src->x.capacity;
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
	if ( bs == 0 || prefix == 0 || suffix == 0 ) {
		return 0;
	}
	size_t pres = bs_size(prefix), sufs = bs_size(suffix);
	size_t origs = bs_size(bs), capacity = bs_capacity(bs);

	char *pre = bs_data(prefix), *suf = bs_data(suffix);
	char *orig = bs_data(bs);
	char *data = orig;

	if ( origs + pres + sufs <= capacity ) {
		if ( bs_is_ptr(bs) ) {
			if ( bs_ref_count(bs) ) {
				ref_minus1(bs);
				data = bs->x.ptr = (char *) malloc(sizeof(char) * capacity);				
				ref_init(bs);
			}
			bs->x.size = pres + origs + sufs;
		} else {
			bs->x.space_left = 15 - pres - origs - sufs;
		}
		memmove(data + pres, orig, origs);		
		memmove(data, pre, pres);
		memmove(data + pres + origs, suf, sufs+1);
	} else {
		
		if ( bs_ref_count(bs) ) {
			xs tmp = xs_literal_empty();
			data = xs_grow(&tmp, pres + origs + sufs);
			memmove(data + pres, orig, origs);
			memmove(data, pre, pres);
			memmove(data + pres + origs, suf, sufs+1);
			bs->x = tmp;
			bs_free(bs); 
		} else {
			orig = data = xs_grow(&bs->x, pres + origs + sufs);
			memmove(data + pres, orig, origs);
			memmove(data, pre, pres);
			memmove(data + pres + origs, suf, sufs+1);
		}
		bs->x.size = pres + origs + sufs;
		ref_init(bs);
	}
	bs->x.is_refer = false;
	return bs;
}
Bstring* bs_trim ( Bstring *bs, const char *trimset ) {
	if ( !trimset[0] ) {
		return bs;
	}
	char *orig = bs_data(bs), *data = orig;
	/* similar to strspn/strpbrk but it operates on binary data */
    uint8_t mask[32] = {0};

#define check_bit(byte) (mask[(uint8_t) byte / 8] & 1 << (uint8_t) byte % 8)
#define set_bit(byte) (mask[(uint8_t) byte / 8] |= 1 << (uint8_t) byte % 8)

    size_t i, slen = bs_size(bs), trimlen = strlen(trimset);
    size_t capacity = bs_capacity(bs);
    for (i = 0; i < trimlen; i++)
        set_bit(trimset[i]);
    for (i = 0; i < slen; i++)
        if (!check_bit(orig[i]))
            break;
    for (; slen > 0; slen--)
        if (!check_bit(orig[slen - 1]))
            break;
    orig += i;
    slen -= i;
    if ( bs_ref_count(bs) ) {
    	ref_minus1(bs);
		data = bs->x.ptr = (char *) malloc(sizeof(char) * capacity);
		ref_init(bs);	
    }
    memmove(data, orig, slen);
    data[slen] = 0;
    if ( bs_is_ptr(bs) ) {
    	bs->x.size = slen;
    } else {
    	bs->x.space_left = 15 - slen;
    }
#undef check_bit
#undef set_bit
    return bs;
}

/* modify value in pos to c */
//void bs_modify_char ( Bstring *bs, int pos, char c );

/* advance */
//void bs_strtok ();
//void bs_strtok_r ();