#include "gmp.h"
#include "gmpxx.h"
class sieve {
    private:
        mpz_t table;
        unsigned int size;

    public:
        sieve(); /* constructor */
        int isPrime(mpz_class r);
        ~sieve(); /* destructor */
};


