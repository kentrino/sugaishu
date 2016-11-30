#include <cstdint>
#include <boost/multiprecision/cpp_int.hpp>

#include <miller_rabin.h>
#include <prime_list.h>

namespace mp = boost::multiprecision;

namespace MillerRabin {
  
// 二乗してもint64_tを超えない値の最大値
const int N_MAX = 3037000499;
const int MEMO_MAX = 500000000;
bool m_[MEMO_MAX] = {};
bool memorized_[MEMO_MAX] = {};

// TODO: これどうにかしたい
inline int64_t mod_squre(int64_t x, int64_t n);
inline int64_t mod_power(int p, int64_t d, int64_t n);

bool test(int64_t n) {
  static int i, j;

  if (n < 2) return false;
  if (n == 2) return true;

  if (n < MEMO_MAX && memorized_[n]) {
    return m_[n];
  }

  static int max_tester_prime_index;
  max_tester_prime_index = 0;

  if (n < 1373653) {
    max_tester_prime_index = 1;
  } else if (n < 2152302898747) {
    max_tester_prime_index = 4;
  } else {
    max_tester_prime_index = 11;
  }

  static int64_t d;
  static int64_t s;
  d = n - 1;
  s = 0;

  while (d % 2 == 0) {
    d /= 2;
    ++s;
  }

  static int64_t x;
  static int p;
  
  // TODO: これ減らす。。。？
  for (i = 0; i < max_tester_prime_index; ++i) {
    bool is_composite = true;
    p = Prime::list[i];
    x = mod_power(p, d, n);
    is_composite = is_composite && (x % n != 1);

    for (j = 0; j < s; j++) {
      is_composite = is_composite && (x % n != n - 1);
      x = mod_squre(x, n);
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

inline int64_t mod_power_small(int64_t p, int64_t d, int64_t n) {
  static int64_t res;

  res = 1;

  while (d >= 1) {
    if (d & 1) {
      res = (res * p) % n;
    }
    d >>= 1;
    p = (p * p) % n;
  }

  return res;
}

inline int64_t mod_power(int p, int64_t d, int64_t n) {
  static int64_t x;
  static mp::int128_t x_int128;

  static int64_t p_int64;
  p_int64 = p;

  if (n < N_MAX) {
    x = mod_power_small(p_int64, d, n);
  } else {
    x_int128 = mp::powm<mp::int128_t>(p, d, n);
    x = static_cast<int64_t>(x_int128);
  }
  return x;
}

inline int64_t mod_squre(int64_t x, int64_t n) {
  static mp::int128_t x_int128;

  if (n < N_MAX) {
    x = x * x % n;
  } else {
    x_int128 = x;
    x_int128 = x_int128 * x_int128 % n;
    x = static_cast<int64_t>(x_int128);
  }

  return x;
}

}
