#include "../../utils.h"


void scalar2_NTT_radix4_base(unsigned *Y, unsigned *X, ull N, ull _root, ull _mod); //This gets called
void scalar2_NTT_rec(ull N, ull n, unsigned *Y, unsigned *X, ull s);
void scalar2_NTT4_base(unsigned *Y, unsigned *X, ull s);
void scalar2_NTT4_twiddle(unsigned *Y, ull s, ull N, ull j);