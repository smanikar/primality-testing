#include <iostream>
#include <fstream>
#include <LiDIA/bigint.h>
#include <LiDIA/bigmod.h>
#include <LiDIA/bigfloat.h>
#include <LiDIA/dlp.h>
#include <LiDIA/polynomial.h>
#include <sys/time.h>
#include <signal.h>
#include "aks.h"

ofstream outFile;
bool aborting = false;

void handle_sigint(int i) {
	if (aborting) {
		cerr << "Aborting...\n";
		outFile.close();
		exit(0);
	} else {
		cerr << "Aborting after current value. Press Ctrl-C again to abort now.\n";
		aborting = true;
	}
	signal(SIGINT, handle_sigint);
}

int main(int argc, char **argv) {
	bigint n, r;
	poly left, right;
	AKSResult result;
	time_t t1, t2;
	
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " <filename>\n\n";
		exit(0);
	}

	signal(SIGINT, handle_sigint);

	ifstream inFile(argv[1]);
	cout << "Checking numbers from file " << argv[1] << "\n";

	outFile.open("output.log");

	cout << "bitlength\tbits\tn\tr\ttime\tResult\n";
	cout << "---------\t----\t-\t-\t----\t------\n";
			 
	while (! inFile.eof()) {
		if (aborting) break;

		inFile >> n;

		time(&t1);
		result = aks_prime_ex(n, r, left, right);
		time(&t2);
		cout << n.bit_length() << "\t" << n << "\t" << r << "\t" << (t2-t1) << "\t" 
			<< right << "\t" << ExplainResult(result) << "\n";
		outFile << n.bit_length() << "\t" << n << "\t" << r << "\t" << (t2-t1) << "\t" 
			<< right << "\t" << ExplainResult(result) << "\n";
	}
	outFile.close();
}
