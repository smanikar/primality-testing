#include <iostream>
#include <fstream>
#include <LiDIA/bigint.h>
#include <LiDIA/bigmod.h>
#include <LiDIA/bigfloat.h>
#include <LiDIA/dlp.h>
#include <LiDIA/polynomial.h>
#include <sys/time.h>
#include "aks.h"


int main(int argc, char **argv) {
	bigint n, r;
	poly left, right;
	AKSResult result;
	time_t t1, t2;
	long nmin = 11000;
	long nmax = 11100;
	
	// Get a value for n to be tested
	// Note that the first Carmichael number is 561
	if (argc > 1) {
		nmin = atol(argv[1]);
		if (argc > 2) {
			nmax = atol(argv[2]);
		} else {
			nmax = nmin;
		}
	} else {
		cout << "Enter number to test: ";
		cin >> nmin;
		nmax = nmin;
		cout << "\n";
	}

	
	cout << "n\tr\ttime\tResult\n";
	cout << "-\t-\t----\t------\n";
	for (n = nmin; n <= nmax; n++) {
		time(&t1);
		result = aks_prime_ex(n, r, left, right);
		time(&t2);
		cout << n << "\t" << r << "\t" << (t2-t1) << "\t" << right << "\t" << ExplainResult(result) << "\n"; 
	}
}
