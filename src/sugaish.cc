#include <iostream>

#include <check.h>
#include <combination.h>
#include <mod_check.h>
#include <prime_list.h>
#include <sugaish.h>
#include <util.h>

using std::endl;
using std::cout;

namespace Sugaish {

void init() {
  ModCheck::init();
}

void find3(int start, int end) {
  int i;

  // 探すsugaishの桁数
  int r = 3;

  start = (start / 6) * 6;
  end = (end / 6) * 6 + 1;

  // TODO: Fix
  if (start < 18) {
    cout << "start must be larger than or equal to 18";
    return;
  }

  Combination *combination;
  int primes[4];
  int *prime_indices;
  int n, i_last_prime;

  for (n = start; n < end; n += 6) {
    if (n % 30 != 0 && n % 30 != 6) {
      continue;
    }
    
    cout << n << endl;

    i_last_prime = Prime::last[n - 1];
    combination = new Combination(i_last_prime, r);
    
    do {
      prime_indices = combination->get();
      for (i = 0; i < r; ++i) {
        primes[i] = Prime::list[*(prime_indices + i)];
      }

      if (!ModCheck::mod5(primes, r, n)) continue;

      if (!ModCheck::mod7(primes, n)) continue;

      if (check3(primes, n)) {
        cout << n << ": " << toString(primes, r) << endl;
      }
    } while (combination->next());

    delete combination;
  }
}

}