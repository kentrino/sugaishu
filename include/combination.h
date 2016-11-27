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
    const int n_;
    const int r_;

    int *result_;
    int64_t *indices_;
    int64_t *max_indices_;

    vector<int> v_;
};

#endif  // SUGAISH_COMBINATION_H_
