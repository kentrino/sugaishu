#include <cstdint>

#include <miller_rabin.h>
#include <prime_list.h>

namespace MillerRabin {
  
const static int MEMO_MAX = 500000000;
bool m_[MEMO_MAX] = {};
bool memorized_[MEMO_MAX] = {};

// TODO: これどうにかしたい
inline int64_t mod_power(int64_t x, int64_t y, int64_t p);

bool test(int64_t n) {
  int i, j;

  if (n < 2) return false;
  if (n == 2) return true;

  if (n < MEMO_MAX && memorized_[n]) {
    return m_[n];
  }

  int max_tester_prime_index = 0;
  if (n < 1373653) {
    max_tester_prime_index = 1;
  } else if (n < 2152302898747) {
    max_tester_prime_index = 4;
  } else {
    max_tester_prime_index = 11;
  }

  int64_t d = n - 1;
  int64_t s = 0;

  while (d % 2 == 0) {
    d /= 2;
    ++s;
  }

  int64_t x;
  int64_t p;
  for (i = 0; i < max_tester_prime_index; ++i) {
    bool is_composite = true;
    p = static_cast<int64_t>(Prime::list[i]);
    x = mod_power(p, d, n);
    is_composite = is_composite && (x % n != 1);

    for (j = 0; j < s; j++) {
      is_composite = is_composite && (x % n != n - 1);
      x = x * x % n;
    }

    if (is_composite) {
      if (n < MEMO_MAX) {
        memorized_[n] = true;
        m_[n] = false;
      }
      return false;
    }
  }
  
  if (n < MEMO_MAX) {
    memorized_[n] = true;
    m_[n] = true;
  }
  return true;
}

/* #include <memory>
void init() {
  std::uninitialized_fill_n(m_, MEMO_MAX, false);
  std::uninitialized_fill_n(memorized_, MEMO_MAX, false);
}*/

inline int64_t mod_power(int64_t p, int64_t y, int64_t n) {
  int64_t res = 1;

  while (y >= 1) {
    if (y & 1) {
      res = (res * p) % n;
    }
    y >>= 1;
    p = (p * p) % n;
  }

  return res;
}

}
