#include "day12.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {
  cout << count_arrangements("???.###", {1, 1, 3}) << " expected 1" << endl;
  // cout << count_arrangements(".??..??...?##.", {1, 1, 3}) << " expected 4"
       // << endl;

  return 0;
}
