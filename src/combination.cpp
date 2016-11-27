typedef unsigned long long llu;
#include <vector>

#include <combination.h>
#include <combination_number.h>

using namespace std;

bool Combination::next() {
  int i = 0;
  int i_to_update = 0;

  if (indices[r - 1] == max_indices[r - 1]) return false;

  for (i = 0; i < r; i++) {
    if (indices[i] < max_indices[i]) {
      i_to_update = i;
      break;
    } 
  }

  result[i_to_update]++;
  
  // rを3等の定数にするだけで10%ほど速くなる
  for (i = 0; i < r; i++) {
    if (i >= i_to_update) {
      indices[i]++;
      continue;
    }

    result[i] = i;
    indices[i] = 1;
      
    if (i == i_to_update - 1) {
      max_indices[i] = CombinationNumber::get(result[i_to_update], i_to_update); 
      continue;
    }

    max_indices[i] = 1;
    continue;
  }
  
  return true;
}

// 出力用
vector<int> Combination::to_vector() {
  v.assign(result, result + r);
  return v;
}

Combination::Combination(int n, int r) : n(n), r(r) {
  int i;

  CombinationNumber::init();

  // この形で初期化できない場合はどうやるか
  result = new int[r];

  // ここのNULL例外はどうやってハンドルするか。いつ失敗するか。
  if (result != NULL) memset(result, 0, r * sizeof *result);

  indices = new int64_t[r];
  if (indices != NULL) memset(indices, 0, r * sizeof *indices);
  
  max_indices = new int64_t[r];
  if (max_indices != NULL) memset(max_indices, 0, r * sizeof *max_indices);

  if (result != NULL && indices != NULL && max_indices != NULL) {
    for (i = 0; i < r; i++) {
      result[i] = i;
      indices[i] = 1;
      if (i == r - 1) {
        max_indices[i] = CombinationNumber::get(n, r);
      } else {
        max_indices[i] = 1; 
      }
    }
  }

  v.resize(r);
}

Combination::~Combination() {
  if(result != NULL) delete [] result;

  if(indices != NULL) delete [] indices;

  if(max_indices != NULL) delete [] max_indices;
}
