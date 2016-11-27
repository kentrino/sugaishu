#include <vector>

#include <combination.h>
#include <combination_number.h>

using std::vector;

bool Combination::next() {
  int i;
  int i_to_update = 0;

  if (indices_[r_ - 1] == max_indices_[r_ - 1]) return false;

  for (i = 0; i < r_; ++i) {
    if (indices_[i] < max_indices_[i]) {
      i_to_update = i;
      break;
    } 
  }

  ++result_[i_to_update];
  
  // rを3等の定数にするだけで10%ほど速くなる
  for (i = 0; i < r_; ++i) {
    if (i >= i_to_update) {
      ++indices_[i];
      continue;
    }

    result_[i] = i;
    indices_[i] = 1;
      
    if (i == i_to_update - 1) {
      max_indices_[i] = CombinationNumber::get(result_[i_to_update], i_to_update); 
      continue;
    }

    max_indices_[i] = 1;
    continue;
  }
  
  return true;
}

// 出力用
vector<int> Combination::to_vector() {
  v_.assign(result_, result_ + r_);
  return v_;
}

Combination::Combination(int n, int r) : n_(n), r_(r) {
  int i;

  CombinationNumber::init();

  // この形で初期化できない場合はどうやるか
  result_ = new int[r_];

  // ここのNULL例外はどうやってハンドルするか。いつ失敗するか。
  if (result_ != NULL) memset(result_, 0, r * sizeof *result_);

  indices_ = new int64_t[r_];
  if (indices_ != NULL) memset(indices_, 0, r * sizeof *indices_);
  
  max_indices_ = new int64_t[r_];
  if (max_indices_ != NULL) memset(max_indices_, 0, r * sizeof *max_indices_);

  if (result_ != NULL && indices_ != NULL && max_indices_ != NULL) {
    for (i = 0; i < r_; ++i) {
      result_[i] = i;
      indices_[i] = 1;
      if (i == r_ - 1) {
        max_indices_[i] = CombinationNumber::get(n_, r_);
      } else {
        max_indices_[i] = 1; 
      }
    }
  }

  v_.resize(r_);
}

Combination::~Combination() {
  if (result_ != NULL) delete [] result_;

  if (indices_ != NULL) delete [] indices_;

  if (max_indices_ != NULL) delete [] max_indices_;
}
