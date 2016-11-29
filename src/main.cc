#include <sugaish.h>

using namespace std;

int main() {
  int i, j;
  
  Sugaish::init();

  // 8976までさがした
  // 7260: [743 5651 6961]
  const static int BASE_N_MIN = 4590;
  const static int BASE_N_MAX = 4650;

  Sugaish::find3(BASE_N_MIN, BASE_N_MAX);
  
  return 0;
}
