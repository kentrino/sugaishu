#include <mod_check.h>

namespace ModCheck {

bool mod5(int (&primes)[4], int r) {
  bool check3 = primes[0] % 5 == 1 && primes[1] % 5 == 1 && primes[2] % 5 == 1;
  if (r == 3) {
    return check3;
  }
  return check3 && primes[3] == 1;
}

}