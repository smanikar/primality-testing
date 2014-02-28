#ifndef __AKS_H
#define __AKS_H

#include <iostream>
#include <LiDIA/bigint.h>
#include <LiDIA/bigmod.h>
#include <LiDIA/bigfloat.h>
#include <LiDIA/dlp.h>
#include <LiDIA/polynomial.h>
using namespace std;
using namespace LiDIA;
typedef polynomial< bigint > poly;

enum AKSResult {AKS_PRIME = 0, AKS_PERFECT_POWER, AKS_GCD, AKS_BIGR, AKS_COMPOSITE};

char *ExplainResult(const AKSResult &r);
void ReduceExponents(polynomial< bigint > &poly, const bigint &r);
void ReduceCoefficients(polynomial< bigint > &poly, const bigint &n);
void ReducePolynomial(polynomial< bigint > &poly, const bigint &r, const bigint &n);
void ReduceByDivision(polynomial< bigint > &poly, const bigint &r);
void ReducedPower(polynomial< bigint > &out, polynomial< bigint > &in, const bigint &r, const bigint &n);
AKSResult aks_prime_ex(const bigint &n, bigint &r, poly &left, poly &right);

#endif
