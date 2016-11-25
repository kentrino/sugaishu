#include <stdio.h>

bool check4(int primes[], int n)
{
  int d[4][4];
  int i, j;

  for (i = 0; i < 4; i++) {
    d[0][i] = primes[i];
    for (j = 1; j < 4; j++) {
      d[j][i] = d[j-1][i] * n;
    }
  }

  int pairs[12][2] = {
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

  int unused[6][2][2] = {
    {{2, 3}, {3, 2}},
    {{1, 3}, {3, 1}},
    {{1, 2}, {2, 1}},
    {{0, 3}, {3, 0}},
    {{0, 2}, {2, 0}},
    {{0, 1}, {1, 0}}
  };

  int number2, number3_1, number3_2, number4_1, number4_2;

  for (i = 0; i < 12; i++) {
    // 二桁の数のチェック
    number2 = d[1][pairs[i][1]] + d[0][pairs[i][0]];

    // 三桁の数のチェック
    number3_1 = number2 + d[2][unused[i/2][0][0]];
    number3_2 = number2 + d[2][unused[i/2][1][0]];

    // 四桁の数のチェック
    number4_1 = number3_1 + d[3][unused[i/2][0][1]];
    number4_2 = number3_2 + d[3][unused[i/2][1][1]];
  }

  return true;
}

bool check3(int primes[], int n)
{
  int d[3][3];
  int i, j;

  for (i = 0; i < 3; i++) {
    d[0][i] = primes[i];
    for (j = 1; j < 3; j++) {
      d[j][i] = d[j-1][i] * n;
    }
  }

  int pairs[6][2] = {
    {0, 1},
    {1, 0},
    {0, 2},
    {2, 0},
    {1, 2},
    {2, 1}
  };

  int unused[3] = {2, 1, 0};

  int number2, number3;

  for (i = 0; i < 6; i++) {
    // 二桁の数のチェック
    number2 = d[1][pairs[i][1]] + d[0][pairs[i][0]];

    // 三桁の数のチェック
    number3 = number2 + d[2][unused[i/2]];
  }

  return true;
}
