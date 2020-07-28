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
    xs *x;
    RefCounter refCount;
} Bstring;


/* allocate/free */
Bstring *bs_empty () {
	Bstring *bs = (Bstring *) malloc(sizeof(Bstring));
	bs->x = xs_newempty();
	ref_init(&bs->refCount);
	return bs;
}
Bstring *bs_new ( const void *p ) {
	Bstring *bs = (Bstring *) malloc(sizeof(Bstring));
	bs->x = xs_new(p);
	ref_init(&bs->refCount);
	return bs;
}
Bstring *bs_free ( Bstring *bs ) {
	xs_free(bs->x);
	ref_free(&bs->refCount);
	return bs;
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