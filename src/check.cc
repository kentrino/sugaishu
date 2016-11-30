#include <cstdint>

#include <check.h>
#include <miller_rabin.h>

bool check3(const int primes[], int n)
{
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
