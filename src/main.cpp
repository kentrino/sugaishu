#include <vector>
#include <cstdio>
#include <iostream>

#include <miller.h>
#include <prime_list.h>
#include <check.h>
#include <combination.h>
#include <util.h>
#include <combination_number.h>

using namespace std;

int main()
{
  int i, j, _n, n, iLastPrime;

  // 探すsugaishの桁数
  int r = 4;

  /* combination を使って組み合わせを羅列
  vector <int> _v;
  unsigned long long lli;

  for (lli = 1; lli <= combination_number(100, 3); lli++) {
    _v = combination(100, 3,lli);
    cout << toString(_v, 3) << endl;
  }

  int N_MAX = 10000 / 6;
  vector<int> v;
  */

  /* combination_next を使って組み合わせを羅列
  int iLastPrime = Prime::last[n - 1];
  v.assign(Prime::list, Prime::list + iLastPrime + 1);

  do {
    cout << toString(v, r) << endl;
  } while (next_combination(v.begin(), v.begin() + r, v.end()));
  */

  Combination *combination = new Combination(100, 3);
  int count = 0;
  do {
    count++;
    //cout << toString(combination->to_vector(), 4) << endl;
  } while (combination->next());
  cout << count << endl;

  CombinationNumber::init();
  cout << CombinationNumber::get(1000, 3) << endl;

  vector<int> v;
  //for (_n = 1; _n < N_MAX; _n++) {
    //n = _n * 6;
    n = 30;

    iLastPrime = Prime::last[n - 1];
    v.assign(Prime::list, Prime::list + iLastPrime + 1);

    do {
      //cout << toString(v, r) << endl;
      /*
      if (check3(v, n)) {
        
      }
      */
    } while (next_combination(v.begin(), v.begin() + r, v.end()));
    
    //cout << count << endl;
  //}

  return 0;
}
