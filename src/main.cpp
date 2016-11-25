#include <vector>
#include <stdio.h>
#include <miller.h>
#include <prime_list.h>
#include "next_combination.h"

bool check(int primes[], int n)
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

int main()
{
  int i;
  int n = 4;
  int r = 2;

  printf("%d\n", Prime::list[10]);
  printf("%d\n", Prime::last[97]);

  std::vector<int> data;
  for (i = 0; i < n; i++) data.push_back(i);

  do {
    printf("[ ");
    for (i = 0; i < r; i++) printf("%d ",data[i]);
    printf("]\n");
  } while (next_combination(data.begin(), data.begin() + r, data.end()));

  return 0;
}