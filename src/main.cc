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

using namespace std;

int main() {
  int i, j;

  const static int BASE_N_MAX = 400;

  // 探すsugaishの桁数
  int r = 3;

  Combination *combination;
  int primes[4];
  int *prime_indices;

  int _n, n, i_last_prime;
  int _n_max = BASE_N_MAX / 6;

  for (_n = 3; _n < _n_max; ++_n) {
    n = _n * 6;

    i_last_prime = Prime::last[n - 1];
    combination = new Combination(i_last_prime, r);
    do {
      prime_indices = combination->get();
      for (i = 0; i < r; ++i) {
        primes[i] = Prime::list[*(prime_indices + i)];
      }
      if (check3(primes, n)) {
        cout << n << ": " << toString(primes, r) << endl;
      }
    } while (combination->next());

    delete combination;
  }
  
  return 0;
}
