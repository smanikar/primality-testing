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
	bigint nmin, nmax;

	cout << "Enter starting number:  ";
	cin >> nmin;
	cout << "Enter finishing number: ";
	cin >> nmax;
	
	ifstream inFile(argv[1]);
	cout << "Checking numbers from " << nmin << " to " << nmax << "\n";

	ofstream outFile("output.log");

	cout << "n\tr\ttime\tResult\n";
	cout << "-\t-\t----\t------\n";

	for (n = nmin; n <= nmax; n++) {
		time(&t1);
		result = aks_prime_ex(n, r, left, right);
		time(&t2);
		cout << n << "\t" << r << "\t" << (t2-t1) << "\t" << right << "\t" << ExplainResult(result) << "\n";
		outFile << n << "\t" << r << "\t" << (t2-t1) << "\t" << right << "\t" << ExplainResult(result) << "\n";
	}
	outFile.close();
}
