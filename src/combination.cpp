// TODO: ここに書く。。。？
#include <vector>
#include <iostream>
#include <util.h>

using namespace std;

// TODO: メモ化する
unsigned long long combination_number(int n, int r)
{
  int i;
  unsigned long long p = 1;
  unsigned long long d = 1;

  int _r = r;
  for (i = 0; i < _r; i++) {
    p *= n;
    d *= r;
    n--;
    r--;
  }

  if (d == 0) {
    return 0;
  }

  return p / d;
}

void combination_unit(int n, int r, unsigned long long k, vector<int> *v, int index)
{
  int i;

  if (r == 1) {
    (*v)[index] = (int)k;
    return;
  }

  // cout << "n: " << n << " r: " << r << " k: " << k << " ================== " <<  endl;  

  int _n = n - 1;
  int _r = r - 1;
  unsigned long long sum = 0;
  for (i = _r; i <= _n; i++) {
    // cout << "_n: " << _n << " _r: " << _r << " i: " << i << endl;
    // cout << "k: " << k << " sum: " << sum << " C: " << combination_number(i, _r) << endl;
    if (k <= sum + combination_number(i, _r)) {
      (*v)[index] = i + 1;
      combination_unit(i, _r, k - sum, v, index + 1);
      return;
    }
    sum += combination_number(i, _r);
  }
}

vector<int> combination(int n, int r, unsigned long long k)
{
  vector<int> v(r);
  fill(v.begin(), v.end(), 0);
  combination_unit(n, r, k, &v, 0);
  return v;
}
