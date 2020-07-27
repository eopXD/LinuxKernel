#include "xs.h"

/* reference counter */
typedef struct refcounter {
    int ref_size, ref_capacity;
    /* array to references */
    xs **ref_ar;
} RefCounter;

void ref_init ( RefCounter *ref ) { 
	ref->ref_size = ref->ref_capacity;
	ref->ref_ar = 0; 
}
void ref_free ( RefCounter *ref ) {
	if ( ref->ref_ar ) {
		free(ref->ref_ar);
	}
	ref_init(ref);
}

/* Better string */
typedef struct Bstring {
    xs *x;
    RefCounter refCount;
} Bstring;


/* declaration */
Bstring *bs_new ( Bstring *bs, const void *p ) {
	bs = (Bstring *) malloc(sizeof(Bstring));
	xs_new(bs->x, p);
	ref_free(&bs->refCount);
	return bs;
}
Bstring *bs_empty ( Bstring *bs ) {
	bs = (Bstring *) malloc(sizeof(Bstring));
	xs_newempty(bs->x);
	ref_free(&bs->refCount);
	return bs;
}
Bstring *bs_free ( Bstring *bs ) {
	bs->x = xs_free(bs->x);
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