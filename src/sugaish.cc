#include <cstdint>
#include <iostream>

#include <combination.h>
#include <miller_rabin.h>
#include <mod_check.h>
#include <prime_list.h>
#include <sugaish.h>
#include <util.h>

using std::endl;
using std::cout;

namespace Sugaish {

bool check3(const int primes[], int n);

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

      if (!ModCheck::mod5(primes, n)) continue;

      if (!ModCheck::mod7(primes, n)) continue;

      if (check3(primes, n)) {
        cout << n << ": " << toString(primes, r) << endl;
      }
    } while (combination->next());

    delete combination;
  }
}

bool check3(const int primes[], int n) {
  const static int pairs[6][2] = {
    {0, 1},
    {1, 0},
    {0, 2},
    {2, 0},
    {1, 2},
    {2, 1}
  };

  const static int unused[3] = {2, 1, 0};

  static int i, j;
  static int64_t d[3][3];
  static int64_t number2, number3;

  for (i = 0; i < 3; i++) {
    d[0][i] = static_cast<int64_t>(primes[i]);
    for (j = 1; j < 3; j++) {
      d[j][i] = static_cast<int64_t>(d[j-1][i] * n);
    }
  }

  for (i = 0; i < 6; i++) {
    // 二桁の数のチェック
    number2 = d[1][pairs[i][1]] + d[0][pairs[i][0]];
    if (!MillerRabin::test(number2)) return false;
    
    // 三桁の数のチェック
    number3 = number2 + d[2][unused[i/2]];
    if (!MillerRabin::test(number3)) return false;
  }

  return true;
}

}
