#include <vector>
#include <cstdio>
#include <iostream>

#include <prime_list.h>
#include <check.h>
#include <combination.h>
#include <util.h>
#include <combination_number.h>
#include <next_combination.h>
#include <miller_rabin.h>
#include <mod_check.h>

using namespace std;

int main() {
  int i, j;

  const static int BASE_N_MIN = 4410;
  const static int BASE_N_MAX = 9000;

  // 探すsugaishの桁数
  int r = 3;

  Combination *combination;
  int primes[4];
  int *prime_indices;

  int n, i_last_prime;

  for (n = BASE_N_MIN; n < BASE_N_MAX; n += 6) {
    if (n % 30 != 0 && n % 30 != 6) {
      continue;
    }

    if (n % 100 == 0 || n > 1000) {
      cout << n << endl;
    }

    i_last_prime = Prime::last[n - 1];
    combination = new Combination(i_last_prime, r);
    do {
      prime_indices = combination->get();
      for (i = 0; i < r; ++i) {
        primes[i] = Prime::list[*(prime_indices + i)];
      }

      if (n % 5 == 1) {
        if (!ModCheck::mod5(primes, r)) continue;
      }

      if (check3(primes, n)) {
        cout << n << ": " << toString(primes, r) << endl;
      }
    } while (combination->next());

    delete combination;
  }
  
  return 0;
}
