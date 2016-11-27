#include <cstdint>
#include <cstdio>

#include <combination_number.h>

#define COMBINATION_N_MAX 1500
#define COMBINATION_R_MAX 4

namespace CombinationNumber {

int64_t m_[COMBINATION_N_MAX][COMBINATION_R_MAX];
bool initialized_ = false;

int64_t calc(const int n, const int r)
{
  int i;
  int64_t factor = 1;
  int64_t divisor = 1;

  int f = n;
  int d = r;

  for (i = 0; i < r; ++i) {
    factor *= f;
    divisor *= d;
    --f;
    --d;
  }

  if (divisor == 0) {
    return 0;
  }

  return factor / divisor;
}

void init() {
  int i, j;
  if (initialized_) return;

  initialized_ = true;
  for (i = 0; i < COMBINATION_N_MAX; ++i) {
    for (j = 0; j < COMBINATION_R_MAX; ++j) {
      m_[i][j] = calc(i, j);
    }
  }
}

int64_t get(int n, int r) {
  if (!initialized_) {
    printf("CombinationNumber is not initialzed.");
    return 0;
  }
  return m_[n][r];
}

}