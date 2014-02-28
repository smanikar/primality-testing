
// LiDIA - a library for computational number theory
//   Copyright (c) 1994, 1995 by the LiDIA Group
//
// File        : dlp.h
// Author      : Damian Weber (DW)
// Last change : TP, Aug 8 1995, initial version
//

#if !defined(LIDIA_DLP_H)
#define LIDIA_DLP_H

#include <LiDIA/bigint.h>
#include <LiDIA/rational_factorization.h>

extern bigint search_generator ( const bigint &p, const bigint &g0,
        rational_factorization &f );

extern bigint pohlig_hellman_shanks ( const bigint &g, const bigint &a,
        const bigint &p, const bigint &q );
extern bigint discrete_log ( const bigint &a, const bigint &b,
        const bigint &p,
        const rational_factorization &f );

#endif
