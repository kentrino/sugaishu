#include <vector>
#include <stdio.h>
#include <miller.h>
#include <prime_list.h>
#include <check.h>
#include <next_combination.h>

int main()
{
  int i, j, _n, n;

  // printf("%d\n", Prime::list[10]);
  // printf("%d\n", Prime::last[97]);

  int m = 10;
  int ps[] = {2, 3, 5};
  check3(ps, m);

  int N_MAX = 10000 / 6;
  for (_n = 0; _n < N_MAX; _n++) {
      n = _n * 6;


  }


  /* combination
  int n = 4;
  int r = 2;

  std::vector<int> data;
  for (i = 0; i < n; i++) data.push_back(i);

  do {
    printf("[ ");
    for (i = 0; i < r; i++) printf("%d ",data[i]);
    printf("]\n");
  } while (next_combination(data.begin(), data.begin() + r, data.end()));
  */
  return 0;
}
