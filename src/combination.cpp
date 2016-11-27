typedef unsigned long long llu;
#include <vector>
#include <iostream>

#include <util.h>
#include <combination.h>

using namespace std;

int64_t combination_number(int n, int r)
{
  int i;
  int64_t factor = 1;
  int64_t divisor = 1;

  int _r = r;
  for (i = 0; i < r; i++) {
    factor *= n;
    divisor *= _r;
    n--;
    _r--;
  }

  if (divisor == 0) {
    return 0;
  }

  return factor / divisor;
}

// TODO: リファレンス引数を使う
// TODO: int64_t を使う
void combination_unit(int n, int r, int64_t k, vector<int> *v, int index)
{
  int i;

  if (r == 1) {
    (*v)[index] = (int)k;
    return;
  }

  int _n = n - 1;
  int _r = r - 1;
  int64_t sum = 0;
  for (i = _r; i <= _n; i++) {
    if (k <= sum + combination_number(i, _r)) {
      (*v)[index] = i + 1;
      combination_unit(i, _r, k - sum, v, index + 1);
      return;
    }
    sum += combination_number(i, _r);
  }
}

vector<int> combination(int n, int r, int64_t k)
{
  vector<int> v(r);
  fill(v.begin(), v.end(), 0);
  combination_unit(n, r, k, &v, 0);
  return v;
}

bool Combination::next() {
  int i;
  int i_to_update;

  if (indices[r - 1] == max_indices[r - 1]) return false;

  for (i = 0; i < 4; i++) {
    if (indices[i] < max_indices[i]) {
      i_to_update = i;
      break;
    } 
  }

  result[i_to_update] += 1;
  
  // indicesの更新
  for (i = i_to_update; i < r; i++) {
    indices[i] += 1;
  }

  // 詰め直し
  for (i = 0; i <= i_to_update; i++) {
    if (i != i_to_update) {
      result[i] = i;
    }
    if (i > 0) {
      indices[i - 1] = 1;
      if (i != i_to_update) {
        max_indices[i - 1] = 1;
      } else {
        max_indices[i_to_update - 1] = combination_number(result[i_to_update], i_to_update); 
      }
    }
  }
  
  return true;
}

vector<int> Combination::to_vector() {
  v.assign(result, result + r);
  return v;
}

Combination::Combination(int n, int r) : n(n), r(r) {
  int i;

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
        max_indices[i] = combination_number(n, r);
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
