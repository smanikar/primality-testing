mpz_pX::mpz_pX() {
    degree = 0;
    coef = (mpz_class**)calloc(1,sizeof(mpz_class*));
    coef[0] = new mpz_class(0);
}
mpz_pX::mpz_pX(unsigned int initial_length) {
    degree = initial_length;
    coef = (mpz_class **)calloc(1,sizeof(mpz_class*)*
            (initial_length+1));
    unsigned int i;
    for(i=0; i<=degree; i++) {
        coef[i] = new mpz_class(0);
    }
}
mpz_pX::mpz_pX(const mpz_pX& o) {
      degree = o.getDegree();
             coef = (mpz_class**)calloc(1,sizeof(mpz_class*)*(degree+1));
