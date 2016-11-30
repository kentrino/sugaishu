#include <sugaish.h>

#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <iostream>
#include <util.h>

using namespace std;


#include <check.h>

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

int code(vector<int> mod_primes, int n) {
  int code;
  code = mod_primes[2];
  code = code * n + mod_primes[1];
  code = code * n + mod_primes[0];
  return code;
}

void build_filter(int filter[], vector<vector<int> > set4s, int n) {
  int i, j;
  const int permutation3[5][3] = {
//  {0, 1, 2},
    {1, 0, 2},
    {0, 2, 1},
    {2, 0, 1},
    {1, 2, 0},
    {2, 1, 0}
  };

  //set<vector<int> > set3s;
  vector<vector<int> >::iterator it;

  for (it = set4s.begin(); it != set4s.end(); ++it) {
    for (i = 0; i < 4; ++i) {
      // セット3に変換してソート
      vector<int> set3;
      vector<int> permutated_set3(3);
      for (j = 0; j < 4; ++j) {
        if (j != i) set3.push_back((*it)[j]);
      }

      for (j = 0; j < 5; ++j) {
        permutated_set3[0] = set3[permutation3[j][0]];
        permutated_set3[1] = set3[permutation3[j][1]];
        permutated_set3[2] = set3[permutation3[j][2]];
        filter[code(set3, 7)] = 1;
      }

      //set3s.insert(set3);
    }
  }
  /*
  set<vector<int> >::iterator sit;
  for (sit = set3s.begin(); sit != set3s.end(); ++sit) {
    cout << toString(*sit, 3) << endl;
    cout << code(*sit, 7) << endl;
  }*/
} 

void init_mod7_filter() {
  const int base = 6;
  const int max = pow(6, 4);
  int i, j, k, n;
  int filter[7][343]; 

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
        cout << toString(numbers, 4) << endl;
      }
    }
    fill(filter[n], filter[n] + 343, 0);
    build_filter(filter[n], numbers_set, 7);
    cout << toString(filter[n], 343) << endl;
  }


}

int main() {
  Sugaish::init();

  // 8976までさがした
  // 7260: [743 5651 6961]
  const int BASE_N_MIN = 3000;
  const int BASE_N_MAX = 9000;
  //vector<int> primes = {4, 4, 1, 1};
  //cout << check4(primes, 4, 7) << endl;
  init_mod7_filter();
  //Sugaish::find3(BASE_N_MIN, BASE_N_MAX);
  
  //int primes[] = {233,3313,3851};
  //check3(primes, 4536);
  //return 0;
}
