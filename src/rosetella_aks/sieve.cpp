#include "sieve.h"
#include <gmp.h>
#include <gmpxx.h>

sieve::sieve() {
    mpz_init(table);
    size = 2;
}

int sieve::isPrime(mpz_class r) {
    unsigned int rul = mpz_get_ui(r.get_mpz_t());

    if(size >= rul) { /* just a lookup */
        return !mpz_tstbit(table,rul);
    }
    else {
        unsigned int oldsize = size;
        size *= 2;

        unsigned int i;
        for(i=2; i<=size; i++) {
            if(!mpz_tstbit(table,i)) {
                unsigned int j;
                for(j=i*2; j<=size; j+=i) {
                    mpz_setbit(table,j);
                }
            }
        }
        return !mpz_tstbit(table,rul);
    }
}

sieve::~sieve() {
    mpz_clear(table);
}


