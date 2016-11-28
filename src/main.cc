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

const static int BASE_N_MAX = 1000;

int main()
{
  int i, j, _n, n, i_last_prime;

  // 探すsugaishの桁数
  int r = 3;
  
  /*
  int ps[] = {17, 23, 193};
  for (i=0; i < 1000000; i++) {
    check3(ps, 228);
  }*/
 
  
  Combination *combination;
  int primes[4];
  int *prime_indices;

  int _n_max = BASE_N_MAX / 6;
  for (_n = 3; _n < _n_max; ++_n) {
    n = _n * 6;

    i_last_prime = Prime::last[n - 1];
    combination = new Combination(i_last_prime, 3);
    do {
      prime_indices = combination->get();
      for (i = 0; i < 3; ++i) {
        primes[i] = Prime::list[*(prime_indices + i)];
      }
      if (check3(primes, n)) {
        cout << "n: " << n <<endl;
        cout << toString(primes, 3) << endl;
      }
    } while (combination->next());

    delete combination;
  }
  
  /*
  n = 228;
  cout << "n: " << n <<endl;

  i_last_prime = Prime::last[n - 1];
  combination = new Combination(i_last_prime, 3);
  do {
    prime_indices = combination->get();
    for (i = 0; i < 3; ++i) {
      primes[i] = Prime::list[*(prime_indices + i)];
    }
    //cout << toString(primes, 3) << endl;
    if (check3(primes, n)) {
      cout << toString(primes, 3) << endl;
    }
  } while (combination->next());

  delete combination;
  */
  return 0;
}
