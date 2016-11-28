#ifndef SUGAISH_MOD_CHECK_H_
#define SUGAISH_MOD_CHECK_H_

#include <cstdint>

namespace ModCheck {

void init();

bool mod5(int (&primes)[4], int r, int n);

bool mod7(int (&primes)[4], int n);

}

#endif  // SUGAISH_MOD_CHECK_H_
