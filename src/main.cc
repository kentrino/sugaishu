#include <sugaish.h>

int main() {
  Sugaish::init();

  // 8976までさがした
  // 7260: [743 5651 6961]
  const int BASE_N_MIN = 3000;
  const int BASE_N_MAX = 9000;

  Sugaish::find3(BASE_N_MIN, BASE_N_MAX);
  
  return 0;
}
