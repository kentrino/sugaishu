#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <vector>

#include <mod_check.h>

using std::fill;
using std::pow;
using std::swap;
using std::unordered_set;
using std::vector;

namespace ModCheck {

// TODO: これで良いの？？
static bool mod7filter_[7][343];

int code(const int primes[], int n);

void init_mod7_filter();

void init() {
  init_mod7_filter();
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
  return mod7filter_[c];
}

bool mod_check4(const vector<int> primes, const int n, const int base) {
  const int pairs[12][2] = {
    {0, 1},
    {1, 0},
    {0, 2},
    {2, 0},
    {0, 3},
    {3, 0},
    {1, 2},
    {2, 1},
    {1, 3},
    {3, 1},
    {2, 3},
    {3, 2},
  };

  const int unused[6][2][2] = {
    {{2, 3}, {3, 2}},
    {{1, 3}, {3, 1}},
    {{1, 2}, {2, 1}},
    {{0, 3}, {3, 0}},
    {{0, 2}, {2, 0}},
    {{0, 1}, {1, 0}}
  };

  int i, j;
  int d[4][4];

  for (i = 0; i < 4; i++) {
    d[0][i] = primes[i];
    for (j = 1; j < 4; j++) {
      d[j][i] = d[j-1][i] * n;
    }
  }

  int number2, number3_1, number3_2, number4_1, number4_2;

  for (i = 0; i < 12; i++) {
    // 二桁の数のチェック
    number2 = d[1][pairs[i][1]] + d[0][pairs[i][0]];
    if (number2 % base == 0) return false;

    // 三桁の数のチェック
    number3_1 = number2 + d[2][unused[i/2][0][0]];
    number3_2 = number2 + d[2][unused[i/2][1][0]];
    if (number3_1 % base == 0) return false;
    if (number3_2 % base == 0) return false;

    // 四桁の数のチェック
    number4_1 = number3_1 + d[3][unused[i/2][0][1]];
    number4_2 = number3_2 + d[3][unused[i/2][1][1]];
    if (number4_1 % base == 0) return false;
    if (number4_2 % base == 0) return false;
  }

  return true;
}

// mod filter作成用
int code(vector<int> mod_primes, int n) {
  int code;
  code = mod_primes[2];
  code = code * n + mod_primes[1];
  code = code * n + mod_primes[0];
  return code;
}

void build_filter(bool filter[], vector<vector<int> > set4s, int base) {
  int i, j;
  const int permutation3[5][3] = {
//  {0, 1, 2},
    {1, 0, 2},
    {0, 2, 1},
    {2, 0, 1},
    {1, 2, 0},
    {2, 1, 0}
  };

  vector<vector<int> >::iterator it;

  for (it = set4s.begin(); it != set4s.end(); ++it) {
    for (i = 0; i < 4; ++i) {
      // セット3に変換して全ての並べ替えをcodeしてfilterに設定
      vector<int> set3;
      vector<int> permutated_set3(3);
      for (j = 0; j < 4; ++j) {
        if (j != i) set3.push_back((*it)[j]);
      }

      for (j = 0; j < 5; ++j) {
        permutated_set3[0] = set3[permutation3[j][0]];
        permutated_set3[1] = set3[permutation3[j][1]];
        permutated_set3[2] = set3[permutation3[j][2]];
        filter[code(set3, base)] = true;
      }
    }
  }
}

void init_mod7_filter() {
  const int base = 6;
  const int max = pow(6, 4);
  int i, j, k, n;

  for (n = 0; n < 7; ++n) {
    vector<vector<int> > numbers_set;
    for (i = 0; i < max; ++i) {
      vector<int> numbers(4);
      k = i;
      for (j = 0; j < 4; ++j) {
        numbers[j] = k % base + 1;
        k = k / base;
      }
      if (mod_check4(numbers, n, 7)) {
        numbers_set.push_back(numbers);
      }
    }
    fill(mod7filter_[n], mod7filter_[n] + 343, false);
    build_filter(mod7filter_[n], numbers_set, 7);
  }
}

int code(const int primes[], int base) {
  static int i;
  static int code;
  static int mod_primes[3];

  for (i = 0; i < 3; ++i) {
    mod_primes[i] = primes[i] % base;
  }

  code = mod_primes[2];
  code = code * base + mod_primes[1];
  code = code * base + mod_primes[0];
  return code;
}

}