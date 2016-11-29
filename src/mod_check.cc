#include <algorithm>
#include <unordered_set>
#include <vector>

#include <mod_check.h>

using std::vector;
using std::swap;
using std::unordered_set;

namespace ModCheck {

// TODO: これで良いの？？
extern const int mod7filter_array_[6][24][3];

// TODO: vector<vectorの方が5%ほど速い
static vector<unordered_set<int> > mod7filter_;

int code(const int primes[], int n);

void init() {
  int i, j;
  mod7filter_.resize(6);
  for (i = 1; i < 6; ++i) {
    mod7filter_[i] = unordered_set<int>();
    for (j = 0; j < 24; ++j) {
      if (mod7filter_array_[i][j][0] != 0) {
        mod7filter_[i].insert(code(mod7filter_array_[i][j], 7));
      }
    }
  }
}

bool mod5(const int primes[], int n) {
  static bool check3;
  if (n % 5 == 0) return true;
  if (n % 5 != 1) return false;
  check3 = primes[0] % 5 == 1 && primes[1] % 5 == 1 && primes[2] % 5 == 1;  
  return check3;
}

// 3桁へのチェックのみ
bool mod7(const int primes[], int n) {
  static int c;
  static unordered_set<int>::iterator it; 
  if (n % 7 == 0) return true;
  if (n % 7 == 6) return false;

  c = code(primes, 7);
  it = mod7filter_[n % 7].find(c);
  if (it != mod7filter_[n].end()) {
    return true;
  }
  return false;
}

void sort(int (&mod_primes)[3]) {
  if (mod_primes[1] > mod_primes[2]) swap(mod_primes[1], mod_primes[2]);
  if (mod_primes[0] > mod_primes[1]) swap(mod_primes[0], mod_primes[1]);
  if (mod_primes[1] > mod_primes[2]) swap(mod_primes[1], mod_primes[2]);
}

int code(const int primes[], int n) {
  static int i;
  static int code;
  static vector<int> v;
  static int mod_primes[3];

  for (i = 0; i < 3; ++i) {
    mod_primes[i] = primes[i] % n;
  }

  sort(mod_primes);

  code = mod_primes[2];
  code = code * n + mod_primes[1];
  code = code * n + mod_primes[0];
  return code;
}

const int mod7filter_array_[6][24][3] = {
  {},
  {
    {1, 1, 1},
    {1, 1, 2},
    {1, 1, 3},
    {1, 2, 2},
    {2, 2, 2},
    {1, 1, 4},
    {2, 3, 3},
    {2, 2, 4},
    {3, 3, 3},
    {1, 4, 4},
    {2, 4, 4},
    {2, 2, 6},
    {1, 5, 5},
    {3, 3, 5},
    {4, 4, 4},
    {3, 3, 6},
    {4, 4, 5},
    {3, 5, 5},
    {3, 6, 6},
    {5, 5, 5},
    {4, 6, 6},
    {5, 5, 6},
    {5, 6, 6},
    {6, 6, 6}
  },
  {
    {1, 1, 6},
    {2, 2, 5},
    {3, 3, 4},
    {3, 4, 4},
    {2, 5, 5},
    {1, 6, 6}
  },
  {
    {1, 1, 1},
    {2, 2, 2},
    {3, 3, 3},
    {4, 4, 4},
    {5, 5, 5},
    {6, 6, 6}
  },
  {
    {1, 1, 6},
    {2, 2, 5},
    {3, 3, 4},
    {3, 4, 4},
    {2, 5, 5},
    {1, 6, 6}
  },
  {
    {1, 1, 1},
    {2, 2, 2},
    {3, 3, 3},
    {4, 4, 4},
    {5, 5, 5},
    {6, 6, 6}
  }
};

}