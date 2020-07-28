#include "xs.h"

typedef struct refcounter {
    int ref_size, ref_capacity;
    xs **ref_ar;
} RefCounter;

void ref_init ( RefCounter *ref ) { 
	ref->ref_size = ref->ref_capacity = 0;
	ref->ref_ar = 0;
}
void ref_free ( RefCounter *ref ) {
	if ( ref->ref_ar ) {
		free(ref->ref_ar);
	}
}

/* Better string */
typedef struct Bstring {
    xs x;
    RefCounter refCount;
} Bstring;

/* utility */
static inline bool bs_is_ptr ( const Bstring *bs ) {
	return xs_is_ptr(&bs->x);
}
static inline char *bs_data ( Bstring *bs ) {
	return xs_data(&bs->x);
}

/* allocate/free */
void bs_newempty ( Bstring *bs ) {
	xs_newempty(&bs->x);
	ref_init(&bs->refCount);
}
void bs_new ( Bstring *bs, const void *p ) {
	xs_new(&bs->x,p);
	ref_init(&bs->refCount);
}

void bs_free ( Bstring *bs ) {
	ref_free(&bs->refCount);
	xs_free(&bs->x);
}


/* basic function */
// usage: dest is a pointer, not allocated yet
//void bs_copy ( Bstring *src, Bstring *dest );
void bs_copy ( Bstring *src, Bstring *dest ) {
/* shallow copy by default */
	/*
	dest = (Bstring *) malloc(sizeof(Bstring));
	dest->x = *xs_newempty();
	if ( bs_is_ptr(src) ) {
		dest->x.ptr = src->x.ptr;
		dest->x.capacity = src->x.capacity;
		dest->x.size = src->x.size;
		src->x.referred = dest->x.refer = true;
	} else {

	}
	*/
}



//void bs_concat ( Bstring *bs, Bstring *prefix, Bstring *suffix );
//void bs_trim ( Bstring *bs, const char *trimset );

/* modify value in pos to c */
//void bs_modify_char ( Bstring *bs, int pos, char c );


/* advance */
//void bs_strtok ();
//void bs_strtok_r ();