#include <iostream>
#include <assert.h>
#include <LiDIA/bigint.h>
#include <LiDIA/bigmod.h>
#include <LiDIA/bigfloat.h>
#include <LiDIA/dlp.h>
#include <LiDIA/polynomial.h>
#include "aks.h"


// Manual inlining of functions could actually decrease performance because it
// may disable the compiler's automatic inlining optimizations. If manual inlining
// is desired, then change this to #define INLINE inline
#define INLINE


char *ExplainResult(const AKSResult &r) {
	switch(r) {
		case AKS_PRIME:			return "Prime";
		case AKS_PERFECT_POWER: 	return "Composite (Perfect Power)";
		case AKS_GCD:			return "Composite (GCD Test)";
		case AKS_BIGR:  		return "Composite (r > n)";
		case AKS_COMPOSITE:		return "Composite (AKS)";
		default:        		return "Unknown";
	}
}



INLINE void ReduceExponents(poly &p, const bigint &r) {
	//-----------------------------------------------------------------------------
	// Reduce polynomial exponents mod r
        //-----------------------------------------------------------------------------
	lidia_size_t i;
	bigint c;
	long newexp;
	long rl;
	
	for (i = p.degree(); i > r; i--) {
		remainder(c, i, r);

		if (c.longify(newexp)) {
			cerr << "Fatal: Reduction too large in line " << __LINE__ << "\n";
			exit(1);
		}
		p[newexp] = p[newexp] + p[i];
		p[i] = 0;
	}
	if (r.longify(rl)) {
		cerr << "Fatal error in line " << __LINE__ << "\n";
		exit(1);
	}

	p.remove_leading_zeros();
}



INLINE void ReduceCoefficients(poly &p, const bigint &n) {
        //-----------------------------------------------------------------------------
	// Reduce polynomial coefficients mod n
        //-----------------------------------------------------------------------------
	lidia_size_t i;
	bigint c;

	for (i = p.degree(); i >= 0; i--) {
		remainder(c, p[i], n);
		p[i] = c;
	}
}



INLINE void ReducePolynomial(poly &p, const bigint &r, const bigint &n) {
        //-----------------------------------------------------------------------------
	// For now, this is implemented in multiple parts for testing. Ultimately,
	// this sould be combined so that reduction of coefficients is performed
	// as the exponents are recalculated (i.e., doing everything at once), but
	// for now this is easier to test.
        //-----------------------------------------------------------------------------
	ReduceCoefficients(p, n);
	ReduceExponents(p, r);
	ReduceCoefficients(p, n);
}



INLINE void ReduceByDivision(poly &p, const bigint &r) {
	//-----------------------------------------------------------------------------
	// Reduce one polynomial by dividing by another fixed polynomial
	// ( x^r - 1 )
        //-----------------------------------------------------------------------------
	poly in = p;
	poly akspoly;
	long rl;

	if(r.longify(rl)) {
		cerr << "Fatal Error: r too large in line " << __LINE__;
		exit(1);
	}

	long x;
#ifdef DEBUG
	assert(2 * rl - 2 <= p.degree());
#endif
	for (x = p.degree(); x >= rl; x--) {
		p[x - rl] = p[x - rl] + p[x];
		p[x] = 0;
	}
	p.remove_leading_zeros();
}



void LongMultiply(poly &p, const poly &in, const poly &in2) {
        //-----------------------------------------------------------------------------
	// First attempt at re-implementing/optimizing multiplication. Right now this
	// is actually slightly slower than LiDIA's native polynomial multiplication.
        //-----------------------------------------------------------------------------
	long new_degree;
	long a,b;
	bigint c;
	bigint d, e;
	poly one;
	one.assign_one();
	
	// If either term is one, we can skip this whole procedure...
	if (in == one) {
		p = in2;
		return;
	} else if (in2 == one) {
		p = in;
		return;
	}

	// Set degree of new polynomial
	new_degree = in.degree() + in2.degree();
	p.set_degree(new_degree);

	// Initialize all coefficients to zero
	for (a = new_degree; a >= 0; a = a - 1) p[a] = 0;

	// Multiply the relevent terms
	for (a = in.degree(); a >= 0; a = a - 1) {
		if (in[a] == 0) continue;	// skip zero terms altogether
		for (b = in2.degree(); b >= 0; b = b - 1) {
			if (in[b] == 0) continue;
			multiply(c, in[a], in2[b]);
			p[a+b] = p[a+b] + c;
		}
	}
	p.remove_leading_zeros();
}



INLINE void Poly2Array(bigint *array, const poly &p1, long n) {
        //-----------------------------------------------------------------------------
	// Convert a polynomial from LiDIA's internal representation to
	// a coefficient array
        //-----------------------------------------------------------------------------
	register long i;
	
	for (i = n; i != -1; i--) {
		array[i] = p1[i];
	}
}



INLINE void Array2Poly(poly &p1, const bigint *array, long n) {
        //-----------------------------------------------------------------------------
	// Convert a polynomial from a coefficient array to LiDIA's representation
        //-----------------------------------------------------------------------------
	register long i;
	p1.set_degree(n);
	for (i = n; i != -1; i--) {
		p1[i] = array[i];
	}
	p1.remove_leading_zeros();
}



INLINE void Square(poly &p1) {
        //-----------------------------------------------------------------------------
	// Square a polynomial
	// 
	// Optimized Implementation: This should cut the number of
	// integer multiplications on the coefficients in half.
	//
	// This implementation currently suffers from performance problems.
	// One potential cause is having to check every coefficient, even those
	// that are zero. A linked-list might have some hope of improving performance,
	// but would be difficult to implement efficiently. Another possibility might
	// be tracking the 'clusters' of nonzero coefficients that will appear
	// next to each other.
        //-----------------------------------------------------------------------------
	long i;			// loop index
	long j;			// loop index
	long n = p1.degree();	// Degree of old polynomial
	long k = n * 2;		// Degree of new polynomial
	long ir;
	bigint a;		// Result of last multiplication
	bigint b;
	bigint c;

	static bigint p[4096];
	static bigint result[4096];

	Poly2Array(p, p1, n);
	for (i = n; i != -1; i--) {
		result[i].assign_zero();
	}

	// Set the first and last terms
	//multiply(result[0], p[0], p[0]);
	//if (k > 0) multiply(result[k], p[n], p[n]);
	
	//square(result[0], p[0]);
	//if (k > 0) square(result[k], p[n]);

	square(result[0], p[0]);
	if (k>0) square(result[k], p[n]);

	// Set intermediate terms
	//for (i = k - 1; i > 0; i--) {
	i = k - 1;
	do {
		ir = i / 2;
		a.assign_zero();
		//for (j = 0; j <= ir; j++) {
		for (j = ir; j >= 0; j--) {
			if (i-j > n) continue;
			if(p[j].is_zero()) continue;
			if(p[i-j].is_zero()) continue;

			/*
			cout << "\nAbout to multiply:  \n";
			cout << "\t   " << p[j] << "\n\t" << " * " << p[i-j] << "\n";
			*/

			multiply(b, p[j], p[i-j]);

			if (j != i - j) {
				// multiply by 2 and add to tally
				//shift_left(c, b, 1);
				multiply(c, b, 2);

				b.assign(a);
				add(a, b, c);
			} else {
				// just add to tally
				c.assign(a);
				add(a, b, c);
			}
		}
		result[i].assign(a);
		i--;
	} while (i > 0);
	
	Array2Poly(p1, result, k);
}




INLINE void ReducedPower(poly &out, poly &in, const bigint &r, const bigint &n) {
        //-----------------------------------------------------------------------------
	// This function performs modular exponentiation of polynomials, reducing
	// at each step.
        //-----------------------------------------------------------------------------
	bigint i;
	poly tmp;
	unsigned int u;
	unsigned int bitlength;

	bitlength = n.bit_length();

	// Using Left-to-right expansion...
	out.assign_one();
	for (u = bitlength; u != 0; u--) {
		//Square(out);				// slower than native version
		multiply(tmp, out, out);
		out = tmp;

		if (n.bit(u - 1) == 1) {
			//LongMultiply(tmp, out, in);	// slower than native version
			multiply(tmp, out, in);
			out = tmp;
		}
		ReduceCoefficients(out, n);
		ReduceByDivision(out, r);
	}
	
	ReduceCoefficients(out, n);
	ReducePolynomial(out, r, n);
}




AKSResult aks_prime_ex(const bigint &n, bigint &r, poly &left, poly &right) {
        //-----------------------------------------------------------------------------
	// This is the main implementation of the AKS algorithm. It primarily follows
	// the version of the algorithm as stated by Granville, p. 16.
	//
	// Note here that there are a number of variables that could be removed as
	// an optimization. They are used separately here for debugging purposes.
        //-----------------------------------------------------------------------------
	bigint b;
	bigfloat logn;		// log of n
	bigfloat logn2;		// log of n squared
	bigint j,q;		
	bigint res;		
	bigint a;		
	bigfloat sqrtr;		// square root of r
	bigfloat sqrtrlogn;	// (square root of r) log n
	bool found_r;		// Flag to indicate whether a suitable value of r has been found yet
	poly p1;		
	bigint x;
	long rl;		// r, expressed as long
	bool ismatch = false;	// Do both sides of equation match?
	bigint nmodr;		// n mod r
	long nmodrl;		// n mod r, expressed as long

	// Paranoia:
	r= 0;
	left.assign_zero();
	right.assign_zero();


	// Step 0: Immediate return on values of 2/3/5 (because other methods get them wrong)
	if (n == 2 || n == 3 || n == 4) return AKS_PRIME;
	

	//-----------------------------------------------------------------------------
	// Step 1: Test whether n is a perfect power
        //-----------------------------------------------------------------------------
	if(is_power(b, n)) return AKS_PERFECT_POWER;


        //-----------------------------------------------------------------------------
	// Step 2: Find a suitable value of r
        //-----------------------------------------------------------------------------
	logn = log((bigfloat)n);
	logn2 = power(logn, 2);
	ceil(q, logn2);

	// Choose value of r
	while(1) {
		found_r= true;
		for (j = 1; j <= logn2; j++) {
			power_mod(res, n, j, q, 0);
			if (res == 1) {
				found_r = false;
				break;
			}
		}
		if (found_r) {
			r = q;
			break;
		}
		q++;
	}
#ifdef DEBUG
	cout << "r = " << r << "\n";
#endif


	//-----------------------------------------------------------------------------
	// If r > n, then we know immediately that n is prime.
	// (From AKS page 3; this was step 4 in the original AKS paper)
        //-----------------------------------------------------------------------------
	if (n <= r) {
		/*
		cout << "r < n   --> PRIME\n";
		cout << "r = " << r << "\n";
		cout << "n = " << n << "\n";
		*/
		//return AKS_BIGR;
		return AKS_PRIME;
	}



	//-----------------------------------------------------------------------------
	// Step 3: GCD Test
        //-----------------------------------------------------------------------------
#ifndef SKIP_GCD
	for (a = 2; a <= r; a++) {
		res = bgcd(a,n);	// Check for performance; could use gcd/bgcd/dgcd (LiDIA p. 39)
		if (res > 1) {
			return AKS_GCD;
		}
	}
#endif


        //-----------------------------------------------------------------------------
	// Final Step: AKS Polynomial comparison
        //-----------------------------------------------------------------------------
	sqrt(sqrtr, r);
	sqrtrlogn = sqrtr * logn;
	
	if(r.longify(rl)) {
		cerr << "Fatal error in line " << __LINE__;
		exit(1);
	}
	for (a = 1; a < sqrtrlogn; a++) {
#ifdef DEBUG
		cout << "testing with a = " << a << "\n";
#endif
		// Calculate the left side of the equation
		p1.set_degree(1);
		p1[1] = 1;
		p1[0] = a;
		ReducedPower(left, p1, r, n);

		// Calculate the right side
		// We avoid using LiDIA's power() function, because it is horribly inefficient, even here.
		remainder(nmodr, n, r);
		nmodr.longify(nmodrl);
		right.assign_zero();
		right.set_degree(nmodrl);
		right[nmodrl] = 1;
		right[0] = a;

		ismatch = (left == right);

#ifdef DEBUG
		// Debugging info...
		cout << "left\t" << left << "\n";
		cout << "right\t" << right << "\n";
		cout << "ismatch\t" << ismatch << "\n";
		cout << "sqrtr\t" << sqrtr << "\n";
		cout << "sqrtrlogn\t" << sqrtrlogn << "\n";
		cout << "logn2\t" << logn2 << "\n";
		cout << "n\t" << n << "\n";
		cout << "j\t" << j << "\n";
		cout << "q\t" << q << "\n";
		cout << "r\t" << r << "\n";
		cout << "a\t" << a << "\n";
		cout << "\n\n";
#endif
#ifndef UNOPTIMIZED
		if (!ismatch) break;
#endif
	}

	if (ismatch) return AKS_PRIME;
	else return AKS_COMPOSITE;
}
