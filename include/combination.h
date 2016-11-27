#ifndef SUGAISH_COMBINATION_H_
#define SUGAISH_COMBINATION_H_

#include <cstdint>
#include <vector>

using namespace std;

class Combination {
  public:
    bool next();
    vector<int> to_vector();
    Combination(int n, int r);
    ~Combination();

  private:
    int n;
    int r;

    int *result;
    int64_t *indices;
    int64_t *max_indices;

    vector<int> v;
};

#endif  // SUGAISH_COMBINATION_H_
